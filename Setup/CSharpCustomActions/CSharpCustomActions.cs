using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Management;
using System.Text;
using WixToolset.Dtf.WindowsInstaller;

namespace CSharpCustomActions
{
    public class CSharpCustomActions
    {
        private static void Execute(string exeFilePath, string arguments, Session session)
        {
            try
            {
                using (var process = new Process())
                {
                    process.StartInfo = new ProcessStartInfo
                    {
                        FileName = exeFilePath,
                        Arguments = arguments,
                        UseShellExecute = false,
                        RedirectStandardOutput = true,
                        RedirectStandardError = true,
                        CreateNoWindow = true
                    };

                    var processName = Path.GetFileNameWithoutExtension(exeFilePath);

                    process.OutputDataReceived += (sender, args) =>
                    {
                        if (!string.IsNullOrEmpty(args.Data))
                            session.Log($"{processName} OUT> {args.Data}");
                    };

                    process.ErrorDataReceived += (sender, args) =>
                    {
                        if (!string.IsNullOrEmpty(args.Data))
                            session.Log($"{processName} ERR> {args.Data}");
                    };

                    process.Start();
                    session.Log($"{exeFilePath} started");

                    process.BeginOutputReadLine();
                    process.BeginErrorReadLine();

                    process.WaitForExit();

                    session.Log($"{processName} exited with code {process.ExitCode}");
                }
            }
            catch (Exception ex)
            {
                session.Log($"Executing '{exeFilePath}' failed: {ex.Message}");
            }
        }

        private static void ListDirectoryContents(string dirpath, StringBuilder list)
        {
            try
            {
                foreach (string dir in Directory.EnumerateDirectories(dirpath))
                    list.AppendLine($" dir  {Path.GetFileName(dir)}");

                foreach (string file in Directory.EnumerateFiles(dirpath))
                    list.AppendLine($" {Path.GetFileName(file)}");
            }
            catch (Exception ex)
            {
                list.AppendLine($"Listing '{dirpath}' failed: {ex.Message}");
            }
        }

        [CustomAction]
        public static ActionResult Preparations(Session session)
        {
            session.Log("CSharpCutsomActions.Preparations begins");

            string choices = string.Empty;
            foreach (var param in session.CustomActionData)
            {
                session.Log($"CustomActionData: {param.Key} = {param.Value}");
                if (param.Value.Trim() == "1")
                {
                    choices += param.Key.ToUpper() + " ";
                }
            }

            string curAssemblyLocation = System.Reflection.Assembly.GetExecutingAssembly().Location;
            if (string.IsNullOrEmpty(curAssemblyLocation))
            {
                session.Log("System.Reflection.Assembly.GetExecutingAssembly().Location failed.");
                return ActionResult.Failure;
            }

            string actionDir = Path.GetDirectoryName(curAssemblyLocation);
            if (actionDir == null)
            {
                session.Log("GetDirectoryName(curAssemblyLocation) failed.");
                return ActionResult.Failure;
            }

            // list dir contents for diagnostic purposes
            // MigrationTool is dynamically linked and needs its dependencies
            var dirContents = new StringBuilder();
            dirContents.AppendLine($"Action directory {actionDir} contents:");
            ListDirectoryContents(actionDir, dirContents);
            session.Log(dirContents.ToString());

            Execute(Path.Combine(actionDir, "migrate.exe"), $"{choices}", session);

            session.Log("CSharpCutsomActions.Preparations succeeded");
            return ActionResult.Success;
        }

    }
}
