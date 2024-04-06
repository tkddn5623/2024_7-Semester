if command -v tmux clear-history &> /dev/null; then
  alias clear='clear; tmux clear-history'
fi

if command -v tmux &> /dev/null && [ -n "$PS1" ] && [[ ! "$TERM" =~ screen ]] && [[ ! "$TERM" =~ tmux ]] && [ -z "$TMUX" ] && [[ ! "$TERM_PROGRAM" =~ vscode ]]; then
  clear
  # exec tmux new -A -s 0 "cat /var/run/motd.dynamic; bash"
  exec tmux new -t 0
fi
