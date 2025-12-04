#!/usr/bin/python3
import argparse

if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument("-i", "--input", help="input gdb source file")
    arg_parser.add_argument("-o", "--output", help="output gdb source file")
    args = vars(arg_parser.parse_args())

    with open(args["input"], "r") as file:
        input_lines = file.readlines()

    output_lines = []
    for _line in input_lines:
        line = _line.strip()
        if line == "":
            pass
        elif line.startswith("#") or line.startswith("set"):
            output_lines.append(line)
        else:
            output_lines.append(rf'printf "(gdb) {line}\n"')
            output_lines.append(line)
            output_lines.append(r"echo \n\n\n")
            output_lines.append("")

    with open(args["output"], "w+") as file:
        file.write("\n".join(output_lines))
