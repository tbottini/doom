"open_windows_terminal_here":
{
  "caption":      "Open Terminal Here...",
  "keys":         ["ctrl+o", "ctrl+t"],
  "flags":        "Windows|IsFile",
  "call":         "Suricate.lib.process.spawn",
  "args":         {"cmd": ["start", "cmd.exe"], "working_dir": "${file_path}"},
  "context_menu": true
}
test