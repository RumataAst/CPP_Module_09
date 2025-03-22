import subprocess

output_file = "test_python.txt"

for X in range(1, 3000, 123):
    print(f"Testing X = {X}")

    for attempt in range(1, 11):
        print(f"  Attempt {attempt}")

        # Generate shuffled sequence with shuf
        try:
            shuf_command = f"shuf -i 1-{X} -n {X}"
            shuf_result = subprocess.check_output(shuf_command, shell=True, text=True).strip()

            # Ensure the result is space-separated
            shuf_result = " ".join(shuf_result.splitlines())
        except subprocess.CalledProcessError as e:
            print(f"Error running shuf: {e}")
            continue

        # Run the Pmerge program with generated sequence
        try:
            pmerge_command = f"./PmergeMe {shuf_result}"
            pmerge_result = subprocess.check_output(pmerge_command, shell=True, text=True)
        except subprocess.CalledProcessError as e:
            # If Pmerge returns a non-zero exit code, capture output anyway
            pmerge_result = e.output
            print(f"Pmerge exited with error code {e.returncode}")

        # Check for error condition in output
        if "Not really sorted" in pmerge_result:
            print("  Found error! Writing to file and stopping.")
            with open(output_file, "w") as f:
                f.write(f"Failed on X = {X}, Attempt = {attempt}\n")
                f.write(f"Initial sequence: {shuf_result}\n")
                f.write(f"Pmerge output:\n{pmerge_result}\n")
            exit(0)

print("Completed all tests with no errors found.")
