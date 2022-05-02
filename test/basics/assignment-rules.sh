#!/bin/bash

cd tmp || { echo "Cannot move to directory: ./tmp" >&2; exit 1; }

total_errors=0

function echo_result() {
  # Usage:
  # - $1: Test number
  # - $2: Test name

  if [[ $? -eq 0 ]]; then
    result="Successful"
    color="\e[32m"
  else
    result="Failed"
    color="\e[31m"

    # Error counter
    total_errors=$(( total_errors + 1 ))
  fi

  echo -e "${color}[${1}] $2 | ${result}\e[0m"
}

allowed_extensions=("cpp" "h" "pro")

# Required file header
error=0
for file in ../src/*.cpp ../src/*.h ../src/*.pro ../Doxyfile ../Makefile; do
  # Source: https://stackoverflow.com/a/965069
  extension="${file#*.}"

  # Skip every file except Makefile, *.c and *.h (different structure)
  if [[ $file != "../Makefile" ]] && [[ $file != "../Doxyfile" ]] && [[ ! "${allowed_extensions[*]}" =~ $extension ]]; then
    # Condition's second part source: https://stackoverflow.com/a/15394738
    continue
  fi

  if [[ "$file" != "../Makefile" ]] && [[ $file != "../Doxyfile" ]]; then
    # C files (*.c and *.h)
    grep -qFi " * @file" "$file" \
      && grep -qF " * ICP project (Class and sequence diagram editor)" "$file" \
      && grep -qFi " * @author " "$file" \
      && continue
  else
    grep -qF "# ICP project (Class and sequence diagram editor)" "$file" \
      && grep -qFi "# Author: " "$file" \
      && continue
  fi

  error=1
  files_without_header+=("$file")
done
[[ $error -eq 0 ]]; echo_result 1 "Files without required header. See CODE_STYLE.md for more info"
[[ ! $error -eq 0 ]] && echo -e "\tFound files without header (or with bad header, check CODE_STYLE.md): ${files_without_header[*]}"

exit "$total_errors"