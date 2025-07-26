#!/bin/bash

# --- Configuration ---
PROJECT_DIR="c-banking-system"
EXECUTABLE="./bankmgmt"
TEST_LOG="test_output.log"
EXPECTED_OUTPUT_DIR="expected_output" # Directory to store expected outputs
DATE_FORMAT="+%d/%m/%Y" # Format for DOB
DATETIME_FORMAT="+%d/%m/%Y %H:%M:%S" # Format for opening date

# --- Colors for output ---
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# --- Functions ---
run_test() {
    local test_name="$1"
    local input_file="$2"
    local expected_output_file="$EXPECTED_OUTPUT_DIR/$test_name.txt"

    echo -e "\n--- Running Test: ${test_name} ---"

    # Run the program with input and capture output
    # Using 'stdbuf -o0' to disable output buffering for real-time interaction simulation
    # Using 'sed' to remove system("clear") escape sequences and sleep delays
    # Using 'grep -v' to remove "Press Any Key to Return Back:" prompts
    # Using 'grep -v' to remove "Enter your choice:" prompts
    # Using 'grep -v' to remove "Enter Customer Account Number:" prompts
    # Using 'grep -v' to remove "Enter Customer PIN:" prompts
    # Using 'grep -v' to remove "Customer DOB (DD/MM/YYYY):" prompts
    # Using 'grep -v' to remove "Customer Account Type(Savings(S)/Current(C)) :" prompts
    # Using 'grep -v' to remove "Enter The Amount For Deposit :" prompts
    # Using 'grep -v' to remove "Enter The Amount For Withdrawal :" prompts
    # Using 'grep -v' to remove "Are you sure you want to delete your account (Y/N)? :" prompts
    # Using 'grep -v' to remove "Welcome to Banking System"
    # Using 'grep -v' to remove menu lines (can be tricky, might need more specific patterns)
    # Using 'grep -v' to remove "Success: Customer name updated." etc. (these are good to keep for verification)

    # A more robust way to clean output for comparison:
    # 1. Remove ANSI escape codes (like clear screen)
    # 2. Remove dynamic elements (account numbers, PINs, dates, timestamps)
    # 3. Remove interactive prompts
    # 4. Normalize whitespace

    # For dynamic values like account number, PIN, and dates, we'll replace them with placeholders
    # in both the actual and expected output for comparison.

    # Generate a unique account number and PIN for this test run
    # In a real test, you might want to pre-define these or capture them from output.
    # For this script, we'll just use placeholders.
    ACCOUNT_NUM_PLACEHOLDER="<ACCOUNT_NUMBER>"
    PIN_PLACEHOLDER="<PIN>"
    DOB_PLACEHOLDER="<DOB>"
    OPENING_DATE_PLACEHOLDER="<OPENING_DATE>"
    TRANSACTION_ID_PLACEHOLDER="<TRANSACTION_ID>"

    # Create a temporary input file with dynamic values if needed
    # For this example, we'll hardcode some values and rely on placeholders for comparison.
    # In a more advanced test, you'd generate these and inject them.

    # Example: Create a temporary input file for account creation
    # This is just illustrative. For a full test, you'd build the input string.
    # For now, we'll use a fixed input string for simplicity.

    # Capture the output
    ACTUAL_OUTPUT=$(
        cat "$input_file" | \
        "$EXECUTABLE" 2>&1 | \
        sed -r "s/\x1B\$([0-9]{1,2}(;[0-9]{1,2})?)?[mGK]//g" | \
        grep -v "Welcome to Banking System" | \
        grep -v "Banking Management Menu" | \
        grep -v "Update Account Menu" | \
        grep -v "----------------------------------" | \
        grep -v "------------------------------------" | \
        grep -v "Enter your choice:" | \
        grep -v "Enter Customer Account Number:" | \
        grep -v "Enter Customer PIN:" | \
        grep -v "Customer Details::" | \
        grep -v "Customer Name :" | \
        grep -v "Customer Address :" | \
        grep -v "Customer Phone Number :" | \
        grep -v "Customer Email :" | \
        grep -v "Customer Account Type(Savings(S)/Current(C)) :" | \
        grep -v "Customer DOB (DD/MM/YYYY):" | \
        grep -v "Enter The Amount For Deposit :" | \
        grep -v "Enter The Amount For Withdrawal :" | \
        grep -v "Are you sure you want to delete your account (Y/N)? :" | \
        grep -v "Press Any Key to Return Back:" | \
        grep -v "Back to main menu.......!" | \
        grep -v "Exiting the program..." | \
        grep -v "Invalid choice! Please try again." | \
        grep -v "Memory allocation failed" | \
        grep -v "Error : No Records Found!..." | \
        grep -v "Error: No Records Found!..." | \
        grep -v "Error: Deposit amount must be greater than zero." | \
        grep -v "Error: Withdrawal amount must be greater than zero." | \
        grep -v "Error: Insufficient funds." | \
        sed 's/Account Number: \$[0-9]\+\$/Account Number: '"$ACCOUNT_NUM_PLACEHOLDER"'/g' | \
        sed 's/PIN: \$[0-9]\+\$/PIN: '"$PIN_PLACEHOLDER"'/g' | \
        sed 's/Date of Birth: \$[0-9\/]\+\$/Date of Birth: '"$DOB_PLACEHOLDER"'/g' | \
        sed 's/Account Opened: \$[0-9\/ :]\+\$/Account Opened: '"$OPENING_DATE_PLACEHOLDER"'/g' | \
        sed 's/transaction_id: \$[0-9]\+\$/transaction_id: '"$TRANSACTION_ID_PLACEHOLDER"'/g' | \
        sed 's/^[[:space:]]*//;s/[[:space:]]*$//' | \
        grep -v '^$' # Remove empty lines
    )

    # Save actual output for debugging
    echo "$ACTUAL_OUTPUT" > "${test_name}_actual.txt"

    # Check if expected output file exists
    if [ ! -f "$expected_output_file" ]; then
        echo -e "${RED}Expected output file not found: ${expected_output_file}${NC}"
        echo "Please create it based on the generated '${test_name}_actual.txt' if this is the first run."
        return 1
    fi

    EXPECTED_OUTPUT=$(cat "$expected_output_file")

    # Compare outputs
    if diff -u <(echo "$EXPECTED_OUTPUT") <(echo "$ACTUAL_OUTPUT"); then
        echo -e "${GREEN}Test '${test_name}' PASSED.${NC}"
        return 0
    else
        echo -e "${RED}Test '${test_name}' FAILED.${NC}"
        echo "Differences found. See diff above and '${test_name}_actual.txt' for actual output."
        return 1
    fi
}

# --- Main Script ---

# Change to project directory
cd "$PROJECT_DIR" || { echo "Error: Project directory '$PROJECT_DIR' not found."; exit 1; }

# Clean previous builds and logs
make clean > /dev/null 2>&1
rm -f "$TEST_LOG" *_actual.txt

# Compile the project
echo "Compiling the project..."
make all > "$TEST_LOG" 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed. Check ${TEST_LOG} for details.${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation successful.${NC}"

# Create expected output directory if it doesn't exist
mkdir -p "$EXPECTED_OUTPUT_DIR"

# --- Test Cases ---

# Test 1: Create Account and View Details
TEST_NAME="create_and_view"
cat << EOF > "${TEST_NAME}_input.txt"
1
John Doe
123 Main St
555-1234
john.doe@example.com
S
01/01/1990
4
<ACCOUNT_NUMBER>
<PIN>
0
EOF
# Note: <ACCOUNT_NUMBER> and <PIN> in input are placeholders for the script,
# but the program will generate real ones. The sed commands in run_test
# will replace the generated ones in the output with these placeholders for comparison.

run_test "$TEST_NAME" "${TEST_NAME}_input.txt"

# Test 2: Deposit Money
TEST_NAME="deposit_money"
cat << EOF > "${TEST_NAME}_input.txt"
5
<ACCOUNT_NUMBER>
<PIN>
500.00
0
EOF
run_test "$TEST_NAME" "${TEST_NAME}_input.txt"

# Test 3: Withdraw Money
TEST_NAME="withdraw_money"
cat << EOF > "${TEST_NAME}_input.txt"
6
<ACCOUNT_NUMBER>
<PIN>
100.00
0
EOF
run_test "$TEST_NAME" "${TEST_NAME}_input.txt"

# Test 4: Update Account (Name and Email)
TEST_NAME="update_account"
cat << EOF > "${TEST_NAME}_input.txt"
2
<ACCOUNT_NUMBER>
<PIN>
1
Jane Doe
4
jane.doe@example.com
0
0
EOF
run_test "$TEST_NAME" "${TEST_NAME}_input.txt"

# Test 5: Delete Account (Confirm)
TEST_NAME="delete_account_confirm"
cat << EOF > "${TEST_NAME}_input.txt"
3
<ACCOUNT_NUMBER>
<PIN>
Y
0
EOF
run_test "$TEST_NAME" "${TEST_NAME}_input.txt"

# --- Final Cleanup ---
echo -e "\nTests finished. Check logs and actual output files for details."
# Optional: rm -f *_input.txt

# Return to original directory
cd - > /dev/null
