#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Connection {
	string from;
	string to;
	int duration;
	Connection(string from, string to, int duration)
		: from(from), to(to), duration(duration)
	{ }
};
ostream& operator<<(ostream& s, const Connection& c) {
	s << c.from << ": " << c.duration << " seconds";
	return s;
}
int main() {
	map<string, vector<Connection>> m;
	ifstream infile("STL-telephones.dat");
	string line = "";
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			vector<int> delimiters;
			delimiters.push_back(-1);
			for (int i = 0; i < line.size(); i++) {
				if (line.at(i) == ' ') {
					delimiters.push_back(i);
				}
			}
			delimiters.push_back(line.size());
			for (int i = 0, j = 0; i < (delimiters.size() - 1) / 3; i++, j += 3) {
				string caller = line.substr(delimiters.at(j) + 1, (delimiters.at(j + 1) - delimiters.at(j) - 1));
				string callee = line.substr(delimiters.at(j + 1) + 1, (delimiters.at(j + 2) - delimiters.at(j + 1) - 1));
				int duration = stoi(line.substr(delimiters.at(j + 2) + 1, (delimiters.at(j + 3) - delimiters.at(j + 2) - 1)));
				Connection* c = new Connection(caller, callee, duration);
				if (m.find(caller) == m.end()) {
					vector<Connection> new_vector;
					new_vector.push_back(*c);
					m.insert({ caller,  new_vector });
				}
				else {
					map<string, vector<Connection>>::iterator iter = m.find(caller);
					iter->second.push_back(*c);
				}
			}
		}
	}
	infile.close();
	string chatterbox;
	int longestTime = 0;

	map<string, vector<Connection>>::iterator iter = m.begin();
	for (int i = 0; i < m.size(); i++) {
		Connection* con = new Connection(iter->first, "", 0);
		for (int i = 0; i < iter->second.size(); i++) {
			con->duration += iter->second.at(i).duration;
		}
		if (con->duration > longestTime) {
			chatterbox = con->from;
			longestTime = con->duration;
		}

		cout << *con << endl;
		iter++;
	}
	map<string, vector<Connection>>::iterator iterMAX = m.find(chatterbox);
	cout << iterMAX->first << " chattered for " << longestTime << " seconds in " << iterMAX->second.size() << " connections" << endl;
	for (int i = 0; i < iterMAX->second.size(); i++) {
		cout << iterMAX->second.at(i).from << " -> " << iterMAX->second.at(i).to << ": " << iterMAX->second.at(i).duration << "s\n";
	}
}
