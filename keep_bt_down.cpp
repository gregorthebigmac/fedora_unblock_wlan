#include "command/command.hpp"
#include <unistd.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int get_bt_line();
vector<string> get_bt_status();
bool is_soft_blocked(string rfkill_soft_blocked);
bool is_hard_blocked(string rfkill_hard_blocked);
string get_time_now();
void write_errors_to_file(vector<string> error_list);
void write_errors_to_file(string error_string);

command cmd;
bool continue_running = true;
int sleep_time = 10000 * 1000;	// sleep_time is in microseconds
int bt_line = 0;

int main() {
	bt_line = get_bt_line();
	while (continue_running) {
		vector<string> bt_status = get_bt_status();
		if (is_soft_blocked(bt_status[bt_line + 1]) == false) {
			vector<string> rfkill_block_bt_feedback, error_list;
			cmd.exec("rfkill block bluetooth", rfkill_block_bt_feedback, error_list);
			if (error_list.size() > 0)
				write_errors_to_file(error_list);
		}
		usleep(sleep_time);	// sleep for 10 seconds.
	}
	return 0;
}

int get_bt_line() {
	vector<string> terminal_feedback, error_list;
	cmd.exec("rfkill list", terminal_feedback, error_list);
	if (error_list.size() > 0) {
		write_errors_to_file(error_list);
		return -1;
	}
	else {
		for (int i = 0; i < terminal_feedback.size(); i++) {
			string temp = terminal_feedback[i];
			int found = temp.find("Bluetooth");
			if (found != string::npos)
				return i;
		}
	}
}

vector<string> get_bt_status() {
	vector<string> terminal_feedback, error_list;
	cmd.exec("rfkill list", terminal_feedback, error_list);
	if (error_list.size() > 0)
		write_errors_to_file(error_list);
	else return terminal_feedback;
}

bool is_soft_blocked(string rfkill_soft_blocked) {
	int found = rfkill_soft_blocked.find("Soft blocked");
	if (found != string::npos) {
		int blocked = rfkill_soft_blocked.find("no");
		if (blocked != string::npos)
			return false;
		else {
			int not_blocked = rfkill_soft_blocked.find("yes");
			if (not_blocked != string::npos)
				return true;
			else write_errors_to_file("rfkill returned bad data, or data was incorrectly parsed.");
		}
	}
	else write_errors_to_file("ERROR: Incorrect line fed to [is_soft_blocked] function! String [Soft Blocked] not found!");
}

bool is_hard_blocked(string rfkill_hard_blocked) {
	int found = rfkill_hard_blocked.find("Hard blocked");
	if (found != string::npos) {
		int blocked = rfkill_hard_blocked.find("no");
		if (blocked != string::npos)
			return false;
		else {
			int not_blocked = rfkill_hard_blocked.find("yes");
			if (not_blocked != string::npos)
				return true;
			else write_errors_to_file("rfkill returned bad data, or data was incorrectly parsed.");
		}
	}
	else write_errors_to_file("ERROR: Incorrect line fed to [is_hard_blocked] function! String [Hard blocked] not found!");
}

string get_time_now() {
	string time_now;
	vector<string> date_and_time, error_list;
	cmd.exec("date +\"%Y-%m-%d %H:%M:%S\"", date_and_time, error_list);
	if (date_and_time.size() > 0) {
		time_now = date_and_time[0];
		return time_now;
	}
	else return "ERROR: Failed to get date and time from system!";
}

void write_errors_to_file(vector<string> error_list) {
	string time_now = get_time_now();
	std::ofstream fout;
	fout.open("errors.log", std::ios_base::app);
	if (fout.is_open()) {
		fout << time_now;
		for (int i = 0; i < error_list.size(); i++) {
			fout << error_list[i];
		}
		fout.close();
	}
	else cout << "Failed to open errors.log!" << endl;
	continue_running = false;
}

// overloaded function in case we merely want to append a string and not a vector of strings
void write_errors_to_file(string error_string) {
	string time_now = get_time_now();
	std::ofstream fout;
	fout.open("errors.log", std::ios_base::app);
	if (fout.is_open()) {
		fout << time_now << "    " << error_string << endl;
		fout.close();
	}
	else cout << "Failed to open errors.log!" << endl;
	continue_running = false;
}