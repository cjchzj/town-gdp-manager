#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<map>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
class File_operate;
class City;
class Operate {
private:
	map<int, vector<City>>city;
public:
	void check_city_year(vector<vector<int>>& a, string n) {
		for (auto& i : city) {
			for (int k = 0; k < i.second.size(); k++) {
				if (n == i.second[k].name) {
					a.push_back({ i.first, k });
				}
			}
		}
	}
	void map_year() {

	}
	void compare_year() {
		cout << "请输入要分析的城市名称：" << endl;
		string n;
		cin >> n;
		vector<vector<int>>city_year;
		check_city_year(city_year, n);
		if (city_year.empty()) {
			cout << "该城市不存在" << endl ;
			return;
		}
		long long p=0, g=0;
		double pg = 0, percent_p = 0, percent_g = 0, percent_pg = 0;
		int size = city_year.size();
		for (int i = 0; i < size; i++) {
			check_city(city_year[i][0], n);
		}
		for (int i = 0; i < size - 1; i++) {
			p += city[city_year[i + 1][0]][city_year[i + 1][1]].population - city[city_year[i][0]][city_year[i][1]].population;
			g += city[city_year[i + 1][0]][city_year[i + 1][1]].gdp - city[city_year[i][0]][city_year[i][1]].gdp;
			pg+= city[city_year[i + 1][0]][city_year[i + 1][1]].gdp/ city[city_year[i + 1][0]][city_year[i + 1][1]].population - city[city_year[i][0]][city_year[i][1]].gdp/ city[city_year[i][0]][city_year[i][1]].population;
			percent_p += (double)(city[city_year[i + 1][0]][city_year[i + 1][1]].population - city[city_year[i][0]][city_year[i][1]].population) / city[city_year[i][0]][city_year[i][1]].population;
			percent_g += (double)(city[city_year[i + 1][0]][city_year[i + 1][1]].gdp - city[city_year[i][0]][city_year[i][1]].gdp) / city[city_year[i][0]][city_year[i][1]].gdp;
			percent_pg += (double)((city[city_year[i + 1][0]][city_year[i + 1][1]].gdp / city[city_year[i + 1][0]][city_year[i + 1][1]].population) - (city[city_year[i][0]][city_year[i][1]].gdp / city[city_year[i][0]][city_year[i][1]].population)) / (city[city_year[i][0]][city_year[i][1]].gdp / city[city_year[i][0]][city_year[i][1]].population);
		}
		cout << fixed << setprecision(2);
		cout << "人口年均增长：" << p / (size - 1) << "增长率：" << (double)percent_p / (size - 1) * 100 << "%" << endl;
		cout << "GDP年均增长：" << g / (size - 1) << "增长率：" << (double)percent_g / (size - 1) * 100 << "%" << endl;
		cout << "人均GDP年均增长：" << (double)pg / (size - 1) << "增长率：" << (double)percent_pg / (size - 1) * 100 << "%" << endl;
	}
	int valid_year() {//校验输入年份合法性
		int n;
		while ((!cin >> n) || (n != 0 && (n < 1980 || n>2026))) {
			cout << "请输入有效年份(1980-2026)" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		return n;
	}
	int valid_check_year() {//校验查询年份合法性
		if (city.empty()) {
			cout << "还未添加数据" << endl;
			return 0;
		}
		cout << "已添加年份：";
		for (auto& i : city) {
			cout << i.first << " ";
		}
		int y;
		cout << endl << "请输入年份" << endl;
		y = valid_year();
		while (!city.count(y)) {
			cout << "请输入已添加年份" << endl;
			cout << "输入0退出" << endl;
			y = valid_year();
			if (y == 0) {
				return 0;
			}
		}
		return y;
	}
	double year_per_gdp(int y) {
		long long pop = year_population(y);
		if (pop == 0) return 0;
		return (double)year_gdp(y) / pop;
	}
	long long year_population(int y) {
		long long ret = 0;
		for (auto& i : city[y]) {
			ret += i.population;
		}
		return ret;
	}
	long long year_gdp(int y) {
		long long ret = 0;
		for (auto& i : city[y]) {
			ret += i.gdp;
		}
		return ret;
	}
	void add() {//添加年份
		int y;
		cout << "请输入年份" <<endl;
		y = valid_year();
		City c;
		c.setcity(y);
		city[y].push_back(c);
		return;
	}
	void delete_all() {//删除全部
		cout << "确认删除按1，退出按任意键" << endl;
		string n;
		cin >> n;
		if (n == "1") {
			City::total_gdp = 0;
			City::total_population = 0;
			city.clear();
			cout << "已删除" << endl;
		}
		else {
			return;
		}
	}
	void delete_year() {//删除一年
		int y = valid_check_year();
		if (y == 0) {
			return;
		}
		cout << "确认删除按1，退出按任意键" << endl;
		string n;
		cin >> n;
		if (n == "1") {
			for (auto& c : city[y]) {
				City::total_gdp -= c.gdp;
				City::total_population -= c.population;
			}
			city.erase(y);
			cout << "已删除" << endl;
		}
		else {
			return;
		}
	}
	void delete_city() {//删城市
		int y = valid_check_year();
		if (y == 0) {
			return;
		}
		cout << "请输入删除城市名" << endl;
		string n2;
		cin >> n2;
		for (int i = 0; i < city[y].size(); i++) {
			if (n2 == city[y][i].name) {
				City::total_gdp -= city[y][i].gdp;
				City::total_population -= city[y][i].population;
				city[y].erase(city[y].begin()+i);
				cout << "已删除" <<endl;
				return;
			}
		}
		cout << "该城市不存在" << endl;
		return;
	}
	void check_year() {//查询年份
		int y = valid_check_year();
		if (y == 0) {
			return;
		}
		cout << "共" << city[y].size() << "个城市  " << endl;
		cout << "总人口：" << year_population(y) << "  总GDP：" << year_gdp(y) << "  人均GDP：" << year_per_gdp(y) << endl;
		return;
	}
	void check_city() {//查询城市
		int y = valid_check_year();
		if (y == 0) {
			return;
		}
		cout << "请输入城市名" <<endl;
		string n2;
		cin >> n2;
		for (int i = 0; i < city[y].size(); i++) {
			if (n2 == city[y][i].name) {
				city[y][i].check();
				return;
			}
		}
		cout << "该城市不存在" << endl;
		return;
	}
	void check_city(int y, string n2) {//查询城市
		for (int i = 0; i < city[y].size(); i++) {
			if (n2 == city[y][i].name) {
				city[y][i].check();
				return;
			}
		}
		return;
	}
	void compare_city() {//同年份两城市比较
		int y = valid_check_year();
		if (y == 0) {
			return;
		}
		long long p1, p2, g1, g2;
		double pg1, pg2;
		string n1, n2;
		cout << "请输入第一个城市的名字";
		cin >> n1;
		cout << "\n请输入第二个城市的名字";
		cin >> n2;
		cout << endl;
		int if_fined1 = 0, if_fined2 = 0;
		for (int i = 0; i < city[y].size(); i++) {
			if (city[y][i].name == n1) {
				p1 = city[y][i].population;
				g1 = city[y][i].gdp;
				pg1 = (double)city[y][i].gdp / city[y][i].population;
				if_fined1++;
			}
			if (city[y][i].name == n2) {
				p2 = city[y][i].population;
				g2 = city[y][i].gdp;
				pg2 = (double)city[y][i].gdp / city[y][i].population;
				if_fined2++;
			}
		}
		if (if_fined1 != 1) {
			cout << n1 << " 不存在" << endl;
		}
		if (if_fined2 != 1) {
			cout << n2 << " 不存在" << endl;
		}
		if (if_fined1 == 1 && if_fined2 == 1) {
			cout << (p1 > p2 ? n1 : n2) << "比" << (p1 < p2 ? n1 : n2) << "人口多" << abs(p1 - p2) << endl;
			cout << (g1 > g2 ? n1 : n2) << "比" << (g1 < g2 ? n1 : n2) << "GDP多" << abs(g1 - g2) << endl;
			cout << (pg1 > pg2 ? n1 : n2) << "比" << (pg1 < pg2 ? n1 : n2) << "人均GDP多" << abs(pg1 - pg2) << endl;
		}
		return;
	}
};
class City {
private:
	long long population, gdp;
	int year;
	string name;
	static long long total_population, total_gdp;
	double per_gdp() {
		if (population == 0) {
			return 0;
		}
		return (double)gdp / population;
	}
	static double total_per_gdp () {
		if (total_population == 0) {
			return 0;
		}
		return (double)total_gdp / total_population;
	}
public:
	City() {
		year = 0;
		name = "none";
		population = 0;
		gdp = 0;
	}
	friend class Operate;
	long long valid_input() {//校验输入合法性
		long long n;
		while ((!cin >> n) || n <= 0) {
			cout << "请输入合法数据" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		return n;
	}
	void setcity(int y) {//输入数据
		cout << "请输入城市名称";
		string n;
		cin >> n;
		cout << "请输入人口：";
		long long p = valid_input();
		cout << "请输入GDP";
		long long g = valid_input();
		name = n;
		population = p;
		gdp = g;
		year = y;
		total_gdp += g;
		total_population += p;
		return;
	}
	void check() {//查询某市数据
		if (population == 0) {
			cout << "请按1输入数据" << endl;
			return;
		}
		cout << "年份：" << year << "  城市：" << name << "  人口：" << population << "  GDP：" << gdp;
		cout << fixed << setprecision(2);
		cout << "  人均GDP：" << per_gdp() << endl;
		return;
	}
	static void total_check() {//查询总数据
		if (total_population == 0) {
			cout << "请按1输入数据" << endl;
			return;
		}
		cout << "总人口：" << total_population;
		cout << fixed << setprecision(2);
		cout << "  总人均GDP：" << total_per_gdp() << endl;
		return;
	}
};
long long City::total_gdp = 0,City::total_population=0;