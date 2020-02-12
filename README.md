# CS344-p3

What this thing needs to do:
- Use the colon symbol (:) as a prompt
- Flush the output buffers *every* time you output
  - `printf("a thing)"; fflush(stdout);`
- Support the following command line format:
  - `command [arg1 arg2 ...] [< input_file] [> output_file] [&]` where
    - `command` is the command,
    - `[arg1 arg2 ...]` are arguments to the command, which are optional,
    - `[< input_file]` redirects from an input file rather than stdin,
    - `[> output_file]` redirects stdout to an output file, and
    - `[&]` denotes a command to run in the background. NOTE: This should only work if the & is the last character in the command.
- Support lines starting with `#` as comments.
  - You do not need to support in-line comments.
- The command line should support a maximum length of 2048 and a maximum argument count of 512.
- Use fork(), exec(), and waitpid() to execute commands.
