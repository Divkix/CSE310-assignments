#!/bin/bash

# Function to run a test case
run_test() {
    local test_file="$1"
    local weighted="$2"
    local undirected="$3"
    local output_file="output_${test_file%.*}.txt"

    echo "Running test: $test_file"

    # Run the program with the test file and capture the output
    if [ "$weighted" = true ]; then
        if [ "$undirected" = true ]; then
            ./adjacencymatrix -w "$test_file" -ud <<EOF
1
2
1
5
3
$output_file
4
1
5
0
EOF
        else
            ./adjacencymatrix -w "$test_file" <<EOF
1
2
1
5
3
$output_file
4
1
5
0
EOF
        fi
    else
        if [ "$undirected" = true ]; then
            ./adjacencymatrix -u "$test_file" -ud <<EOF
1
2
1
5
3
$output_file
4
1
5
0
EOF
        else
            ./adjacencymatrix -u "$test_file" <<EOF
1
2
1
5
3
$output_file
4
1
5
0
EOF
        fi
    fi

    echo "Test completed for: $test_file"
    echo "Output saved to: $output_file"
    echo "---"
}

# Run tests
run_test "graph1.txt" false false
run_test "graph2.txt" true true
run_test "graph3.txt" true false
run_test "graph4.txt" false true
