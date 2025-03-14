#include <bits/stdc++.h>
using namespace std;

struct Process
{
	int id;
	int priority;
	int arrival_time;
	vector<int> bursts;
};

class FCFS
{
public:
	vector<vector<char>> fcfs(vector<Process> processes)
	{
		int n = processes.size();
		vector<vector<char>> gantt(n);
		vector<int> burst_number(n, -1);
		vector<bool> burst_complete(n, false);
		queue<pair<int, Process *>> ready_q;
		queue<pair<int, Process *>> io_q;
		pair<int, int> cpu_process = {0, -1};
		pair<int, int> io_process = {0, -1};

		int time_stamp = 0;
		int terminate = 0;
		for (int i = 0; i < n; i++)
		{
			terminate = terminate || burst_number[i];
		}
		while (terminate)
		{
			for (int i = 0; i < n; i++)
			{
				if (processes[i].arrival_time > time_stamp)
				{
					gantt[i].push_back('_');
					continue;
				}
				if (burst_number[i] == -1)
				{
					burst_number[i] = 1;
					if (burst_number[i] > processes[i].bursts.size())
					{
						gantt[i].push_back('_');
						burst_number[i] = 0;
					}
					else
					{
						gantt[i].push_back('W');
						ready_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
					}
				}
				else if (burst_number[i] == 0)
				{
					gantt[i].push_back('_');
				}
				else if (burst_number[i] % 2 == 1)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('B');
							io_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('W');
					}
				}
				else if (burst_number[i] % 2 == 0)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('W');
							ready_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('B');
					}
				}
			}

			if (cpu_process.first == 0)
			{
				if (ready_q.empty())
				{
					cpu_process = {0, -1};
				}
				else
				{
					auto next = ready_q.front();
					ready_q.pop();
					cpu_process = {next.first, next.second->id};
					gantt[cpu_process.second - 1][gantt[cpu_process.second - 1].size() - 1] = 'C';
					cpu_process.first--;
					if (cpu_process.first == 0)
					{
						burst_complete[cpu_process.second - 1] = true;
					}
				}
			}
			else
			{
				gantt[cpu_process.second - 1][gantt[cpu_process.second - 1].size() - 1] = 'C';
				cpu_process.first--;
				if (cpu_process.first == 0)
				{
					burst_complete[cpu_process.second - 1] = true;
				}
			}
			if (io_process.first == 0)
			{
				if (io_q.empty())
				{
					io_process = {0, -1};
				}
				else
				{
					auto next = io_q.front();
					io_q.pop();
					io_process = {next.first, next.second->id};
					gantt[io_process.second - 1][gantt[io_process.second - 1].size() - 1] = 'R';
					io_process.first--;
					if (io_process.first == 0)
					{
						burst_complete[io_process.second - 1] = true;
					}
				}
			}
			else
			{
				gantt[io_process.second - 1][gantt[io_process.second - 1].size() - 1] = 'R';
				io_process.first--;
				if (io_process.first == 0)
				{
					burst_complete[io_process.second - 1] = true;
				}
			}

			time_stamp++;

			terminate = 0;
			for (int i = 0; i < n; i++)
			{
				terminate = terminate || burst_number[i];
			}
		}
		return gantt;
	}
};

class STRF
{
public:
	vector<vector<char>> strf(vector<Process> processes)
	{
		int n = processes.size();
		vector<vector<char>> gantt(n);
		vector<int> burst_number(n, -1);
		vector<bool> burst_complete(n, false);
		priority_queue<pair<int, Process *>, vector<pair<int, Process *>>, greater<pair<int, Process *>>> ready_q;
		queue<pair<int, Process *>> io_q;
		pair<int, Process *> cpu_process = {0, NULL};
		pair<int, int> io_process = {0, -1};

		int time_stamp = 0;
		int terminate = 0;
		for (int i = 0; i < n; i++)
		{
			terminate = terminate || burst_number[i];
		}
		while (terminate)
		{
			for (int i = 0; i < n; i++)
			{
				if (processes[i].arrival_time > time_stamp)
				{
					gantt[i].push_back('_');
					continue;
				}
				if (burst_number[i] == -1)
				{
					burst_number[i] = 1;
					if (burst_number[i] > processes[i].bursts.size())
					{
						gantt[i].push_back('_');
						burst_number[i] = 0;
					}
					else
					{
						gantt[i].push_back('W');
						ready_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
					}
				}
				else if (burst_number[i] == 0)
				{
					gantt[i].push_back('_');
				}
				else if (burst_number[i] % 2 == 1)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('B');
							io_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('W');
					}
				}
				else if (burst_number[i] % 2 == 0)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('W');
							ready_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('B');
					}
				}
			}

			ready_q.push(cpu_process);
			cpu_process = ready_q.top();
			ready_q.pop();
			if (cpu_process.first == 0)
			{
				if (ready_q.empty())
				{
					cpu_process = {0, NULL};
				}
				else
				{
					auto next = ready_q.top();
					ready_q.pop();
					cpu_process = {next.first, next.second};
					gantt[cpu_process.second->id - 1][gantt[cpu_process.second->id - 1].size() - 1] = 'C';
					cpu_process.first--;
					if (cpu_process.first == 0)
					{
						burst_complete[cpu_process.second->id - 1] = true;
					}
				}
			}
			else
			{
				gantt[cpu_process.second->id - 1][gantt[cpu_process.second->id - 1].size() - 1] = 'C';
				cpu_process.first--;
				if (cpu_process.first == 0)
				{
					burst_complete[cpu_process.second->id - 1] = true;
				}
			}
			if (io_process.first == 0)
			{
				if (io_q.empty())
				{
					io_process = {0, -1};
				}
				else
				{
					auto next = io_q.front();
					io_q.pop();
					io_process = {next.first, next.second->id};
					gantt[io_process.second - 1][gantt[io_process.second - 1].size() - 1] = 'R';
					io_process.first--;
					if (io_process.first == 0)
					{
						burst_complete[io_process.second - 1] = true;
					}
				}
			}
			else
			{
				gantt[io_process.second - 1][gantt[io_process.second - 1].size() - 1] = 'R';
				io_process.first--;
				if (io_process.first == 0)
				{
					burst_complete[io_process.second - 1] = true;
				}
			}

			time_stamp++;

			terminate = 0;
			for (int i = 0; i < n; i++)
			{
				terminate = terminate || burst_number[i];
			}
		}
		return gantt;
	}
};

class PRIORITY_PREEMPTIVE
{
public:
	vector<vector<char>> priority_preemptive(vector<Process> processes)
	{
		int n = processes.size();
		vector<vector<char>> gantt(n);
		vector<int> burst_number(n, -1);
		vector<bool> burst_complete(n, false);
		priority_queue<pair<int, pair<int, Process *>>, vector<pair<int, pair<int, Process *>>>, greater<pair<int, pair<int, Process *>>>> ready_q;
		queue<pair<int, Process *>> io_q;
		pair<int, pair<int, Process *>> cpu_process = {INT_MAX, {0, NULL}};
		pair<int, int> io_process = {0, -1};

		int time_stamp = 0;
		int terminate = 0;
		for (int i = 0; i < n; i++)
		{
			terminate = terminate || burst_number[i];
		}
		while (terminate)
		{
			for (int i = 0; i < n; i++)
			{
				if (processes[i].arrival_time > time_stamp)
				{
					gantt[i].push_back('_');
					continue;
				}
				if (burst_number[i] == -1)
				{
					burst_number[i] = 1;
					if (burst_number[i] > processes[i].bursts.size())
					{
						gantt[i].push_back('_');
						burst_number[i] = 0;
					}
					else
					{
						gantt[i].push_back('W');
						ready_q.push({processes[i].priority, {processes[i].bursts[burst_number[i] - 1], &processes[i]}});
					}
				}
				else if (burst_number[i] == 0)
				{
					gantt[i].push_back('_');
				}
				else if (burst_number[i] % 2 == 1)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('B');
							io_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('W');
					}
				}
				else if (burst_number[i] % 2 == 0)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('W');
							ready_q.push({processes[i].priority, {processes[i].bursts[burst_number[i] - 1], &processes[i]}});
						}
					}
					else
					{
						gantt[i].push_back('B');
					}
				}
			}

			if (cpu_process.second.first == 0)
			{
				if (ready_q.empty())
				{
					cpu_process = {INT_MAX, {0, NULL}};
				}
				else
				{
					auto next = ready_q.top();
					ready_q.pop();
					cpu_process = next;
					gantt[cpu_process.second.second->id - 1][gantt[cpu_process.second.second->id - 1].size() - 1] = 'C';
					cpu_process.second.first--;
					if (cpu_process.second.first == 0)
					{
						burst_complete[cpu_process.second.second->id - 1] = true;
					}
				}
			}
			else
			{
				ready_q.push(cpu_process);
				cpu_process = ready_q.top();
				ready_q.pop();
				gantt[cpu_process.second.second->id - 1][gantt[cpu_process.second.second->id - 1].size() - 1] = 'C';
				cpu_process.second.first--;
				if (cpu_process.second.first == 0)
				{
					burst_complete[cpu_process.second.second->id - 1] = true;
				}
			}

			if (io_process.first == 0)
			{
				if (io_q.empty())
				{
					io_process = {0, -1};
				}
				else
				{
					auto next = io_q.front();
					io_q.pop();
					io_process = {next.first, next.second->id};
					gantt[io_process.second - 1][gantt[io_process.second - 1].size() - 1] = 'R';
					io_process.first--;
					if (io_process.first == 0)
					{
						burst_complete[io_process.second - 1] = true;
					}
				}
			}
			else
			{
				gantt[io_process.second - 1][gantt[io_process.second - 1].size() - 1] = 'R';
				io_process.first--;
				if (io_process.first == 0)
				{
					burst_complete[io_process.second - 1] = true;
				}
			}

			time_stamp++;

			terminate = 0;
			for (int i = 0; i < n; i++)
			{
				terminate = terminate || burst_number[i];
			}
		}
		return gantt;
	}
};

class RR
{
public:
	vector<vector<char>> rr(vector<Process> processes)
	{
		int n = processes.size();
		vector<vector<char>> gantt(n);
		vector<int> burst_number(n, -1);
		vector<bool> burst_complete(n, false);
		queue<pair<int, Process *>> ready_q;
		queue<pair<int, Process *>> io_q;
		pair<int, Process *> cpu_process;
		pair<int, Process *> io_process;

		int time_stamp = 0;
		int terminate = 0;
		for (int i = 0; i < n; i++)
		{
			terminate = terminate || burst_number[i];
		}
		while (terminate)
		{
			for (int i = 0; i < n; i++)
			{
				if (processes[i].arrival_time > time_stamp)
				{
					gantt[i].push_back('_');
					continue;
				}
				if (burst_number[i] == -1)
				{
					burst_number[i] = 1;
					if (burst_number[i] > processes[i].bursts.size())
					{
						gantt[i].push_back('_');
						burst_number[i] = 0;
					}
					else
					{
						gantt[i].push_back('W');
						ready_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
					}
				}
				else if (burst_number[i] == 0)
				{
					gantt[i].push_back('_');
				}
				else if (burst_number[i] % 2 == 1)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('B');
							io_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('W');
					}
				}
				else if (burst_number[i] % 2 == 0)
				{
					if (burst_complete[i])
					{
						burst_complete[i] = false;
						burst_number[i]++;
						if (burst_number[i] > processes[i].bursts.size())
						{
							gantt[i].push_back('_');
							burst_number[i] = 0;
						}
						else
						{
							gantt[i].push_back('W');
							ready_q.push({processes[i].bursts[burst_number[i] - 1], &processes[i]});
						}
					}
					else
					{
						gantt[i].push_back('B');
					}
				}
			}

			if (ready_q.empty())
			{
				ready_q.push({0, NULL});
			}
			if (io_q.empty())
			{
				io_q.push({0, NULL});
			}

			cpu_process = ready_q.front();
			ready_q.pop();
			if (cpu_process.first == 0)
			{
				if (ready_q.empty())
				{
					ready_q.push({0, NULL});
				}
				else
				{
					auto next = ready_q.front();
					ready_q.pop();
					cpu_process = next;
					gantt[cpu_process.second->id - 1][gantt[cpu_process.second->id - 1].size() - 1] = 'C';
					cpu_process.first--;
					if (cpu_process.first == 0)
					{
						burst_complete[cpu_process.second->id - 1] = true;
					}
					else
					{
						ready_q.push(cpu_process);
					}
				}
			}
			else
			{
				gantt[cpu_process.second->id - 1][gantt[cpu_process.second->id - 1].size() - 1] = 'C';
				cpu_process.first--;
				if (cpu_process.first == 0)
				{
					burst_complete[cpu_process.second->id - 1] = true;
				}
				else
				{
					ready_q.push(cpu_process);
				}
			}

			io_process = io_q.front();
			io_q.pop();
			if (io_process.first == 0)
			{
				if (io_q.empty())
				{
					io_process = {0, NULL};
				}
				else
				{
					auto next = io_q.front();
					io_q.pop();
					io_process = next;
					gantt[io_process.second->id - 1][gantt[io_process.second->id - 1].size() - 1] = 'R';
					io_process.first--;
					if (io_process.first == 0)
					{
						burst_complete[io_process.second->id - 1] = true;
					}
					else
					{
						io_q.push(io_process);
					}
				}
			}
			else
			{
				gantt[io_process.second->id - 1][gantt[io_process.second->id - 1].size() - 1] = 'R';
				io_process.first--;
				if (io_process.first == 0)
				{
					burst_complete[io_process.second->id - 1] = true;
				}
				else
				{
					io_q.push(io_process);
				}
			}

			time_stamp++;

			terminate = 0;
			for (int i = 0; i < n; i++)
			{
				terminate = terminate || burst_number[i];
			}
		}
		return gantt;
	}
};

void readProcess(vector<Process> &processes)
{
	cout << endl;
	cout << "Data is read from " << "prod.dat " << endl;
	cout << endl;
	ifstream file("prod.dat");
	if (!file.is_open())
	{
		cerr << "Error in opening file" << endl;
		return;
	}

	int n;
	file >> n;
	file.ignore();

	for (int i = 0; i < n; i++)
	{
		string line;
		getline(file, line);
		stringstream ss(line);

		Process p;
		ss >> p.id;
		ss.ignore();
		ss >> p.priority;
		ss.ignore();
		ss >> p.arrival_time;
		ss.ignore();
		int burst;
		while (ss >> burst)
		{
			if (burst == -1)
				break;
			p.bursts.push_back(burst);
			if (ss.peek() == ',')
			{
				ss.ignore();
				ss.ignore();
			}
		}
		ss.ignore();
		processes.push_back(p);
	}

	file.close();
}

void displayPeocessStatus(vector<vector<char>> &status)
{
	int n = status.size();
	for (int i = 0; i < n; i++)
	{
		cout << "P" << i + 1 << "\t";
		for (char c : status[i])
		{
			cout << c << " ";
		}
		cout << endl;
	}
}

int main()
{
	vector<Process> processes;
	readProcess(processes);

	cout << "Symbols: " << endl;
	cout << "C: running (CPU scheduled)" << endl;
	cout << "W: waiting for CPU" << endl;
	cout << "B: blocked for IO" << endl;
	cout << "R: running on IO" << endl;
	cout << "_: process not yet come or completed" << endl;
	cout << endl;

	cout << "History of Process Status using FCFS: " << endl;
	FCFS fcfs1;
	vector<vector<char>> gantt_fcfs = fcfs1.fcfs(processes);
	displayPeocessStatus(gantt_fcfs);
	cout << endl;

	cout << "History of Process Status using SJF(Preemptive): " << endl;
	STRF strf1;
	vector<vector<char>> gantt_strf = strf1.strf(processes);
	displayPeocessStatus(gantt_strf);
	cout << endl;

	cout << "History of Process Status using PRIORITY(Preemptive): " << endl;
	PRIORITY_PREEMPTIVE priority_preemptive1;
	vector<vector<char>> gantt_priority_preemptive = priority_preemptive1.priority_preemptive(processes);
	displayPeocessStatus(gantt_priority_preemptive);
	cout << endl;

	cout << "History of Process Status using RR: " << endl;
	RR rr1;
	vector<vector<char>> gantt_rr = rr1.rr(processes);
	displayPeocessStatus(gantt_rr);
	cout << endl;

	return 0;
}