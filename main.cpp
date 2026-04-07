#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
class Fileoperate;
class Operate;
class Town {
private:
	long long gdp,people;
	static long long total_gdp,total_people;
	double cal_per_gdp() {
		if (people != 0)
			return (double)gdp / people;
		return 0;
	}
	static double cal_per_gdp_total() {
		if (total_people != 0)
			return (double)total_gdp / total_people;
		return 0;
	}
public:
	Town() {
		gdp = 0, people = 0;
	}
	friend class Operate;
	friend class Fileoperate;//加载数据要重置静态成员的值
	long long getpeople() {
		return people;
	}
	long long getgdp() {
		return gdp;
	}
	void setload(long long p, long long g) {//加载数据
		people = p;
		gdp = g;
		total_gdp += gdp;
		total_people += people;
	}
	void SetValue();
	long long getlonglong() {//people和gdp校验输入合法性
		long long m;
		while (!(cin >> m) || m <= 0) {
			cout << "请输入有效数据" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		return m;
	}
	void display() {
		if (people == 0) {
			cout << "未输入有效数据" << endl;
			return;
		}
		cout << fixed << setprecision(2);
		cout << "该镇人均GDP为" << cal_per_gdp() << "元" << endl;
	}
	static void display_total() {
		if (total_people == 0) {
			cout << "未输入有效数据" << endl;
			return;
		}
		cout << "总人数为" << total_people << "  总GDP为" << total_gdp << "元" << endl;
		cout << fixed << setprecision(2);
		cout << "总人均GDP为" << cal_per_gdp_total() << "元" << endl;
	}
};
long long Town::total_gdp = 0, Town::total_people = 0;
void Town::SetValue() {
	long long p, g;
	cout << "请输入该镇人口：";
	p = getlonglong();
	cout << "请输入该镇GDP：";
	g = getlonglong();
	gdp = g;
	people = p;
	total_gdp += gdp;
	total_people += people;
}
vector<Town>town;
class Operate {
public:
	void gettown() {//查询数据
		if (town.size() == 0) {
			cout << "未添加数据" << endl;
			return;
		}
		int m;
		cout << "请输入城镇编号" << endl;
		while (!(cin >> m) || m <= 0 || m > town.size()) {//校验输入合法性
			cout << "请输入有效数据" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		town[m - 1].display();
	}
	int getoperate() {//操作校验输入合法性
		int m;
		cout << "请输入操作" << endl;
		while (!(cin >> m) || m <= 0 || m > 6) {
			cout << "请输入有效操作，按1添加城镇，按2查询城镇，按3查询总数据，按4删除城镇数据，按5清空数据，按6退出程序" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		return m;
	}
	void deletetown() {
		if (town.size() == 0) {
			cout << "已清空数据";
			return;
		}
		int m;
		cout << "请输入删除城镇编号" << endl;
		while (!(cin >> m) || m <= 0 || m > town.size()) {//校验输入合法性
			cout << "请输入有效数据" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		Town::total_people -= town[m - 1].people;
		Town::total_gdp -= town[m - 1].gdp;
		town.erase(town.begin() + m - 1);
		cout << "已删除" <<endl;
	}
};
class Fileoperate {
public:
	void save() {//存
		ofstream file("town.txt");
		for (int i = 0; i < town.size(); i++) {
			file << town[i].getpeople() << " " << town[i].getgdp() << endl;
		}
		file.close();
	}
	void load() {//读取
		ifstream file("town.txt");
		if (!file) {
			return;
		}
		town.clear();
		Town::total_gdp = 0;
		Town::total_people = 0;
		long long People, Gdp;
		while (file >> People >> Gdp) {
			Town t;
			t.setload(People, Gdp);
			town.push_back(t);
		}
		file.close();
	}
	void clear_all() {
		if (town.empty()) {
			cout << "已无数据" << endl;
			return;
		}
		town.clear();
		Town::total_gdp = 0;
		Town::total_people = 0;
		cout << "已清空所有城镇数据" << endl;
	}
};
int main() {
	Fileoperate fileoperate;
	fileoperate.load();
	int n;
	Operate operate;
	while (1) {
		cout << "请进行操作，按1添加城镇数据，按2查询城镇数据，按3查询总数据，按4删除城镇数据，按5清空数据，按6退出程序" <<endl;
		n = operate.getoperate();
		if (n == 1) {
			Town t;
			t.SetValue();
			town.push_back(t);
		}
		else if (n == 2) {
			operate.gettown();
		}
		else if (n == 3) {
			Town::display_total();
		}
		else if (n == 4) {
			operate.deletetown();
		}
		else if (n == 5) {
			fileoperate.clear_all();
		}
		else {
			fileoperate.save();
			return 0;
		}
	}
}