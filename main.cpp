#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<map>
#include<string>
#include<algorithm>
#include<cmath>
#include<climits>
using namespace std;
class File_operate;
class Operate;
class City;
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
	static double total_per_gdp() {
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
		while (!(cin >> n) || n <= 0) {
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
	void draw(vector<vector<int>>& xy, int len, int height) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < len; x++) {
				int z = 0;
				for (int i = 0; i < xy.size(); i++) {
					if (xy[i][0] == x && xy[i][1] == y) {
						cout << "@";
						z = 1;
						break;
					}
				}
				if(z)
				    cout << ".";
				if (x == len - 1) {
					cout << endl << endl;
				}
			}
		}
	}
	void map_year(vector<vector<int>>& a, int y) {
		int len = 40, height = 10;
		int size_len = len / a.size();
		if (size_len == 0) {
			size_len = 1;
		}
		vector<vector<int>>pxy;
		vector<vector<int>>gxy;
		vector<vector<int>>pgxy;
		int n = 1, startx = 1, starty = 1;
		long long max1 = LLONG_MIN, min1 = LLONG_MAX;
		long long max2 = LLONG_MIN, min2 = LLONG_MAX;
		double max3 = -1e18, min3 = 1e18;
		for (int i = 0; i < a.size(); i++) {
			long long temp1 = city[a[i][0]][a[i][1]].population;
			if (temp1 > max1) {
				max1 = temp1;
			}
			if (temp1 < min1) {
				min1 = temp1;
			}
			long long temp2 = city[a[i][0]][a[i][1]].gdp;
			if (temp2 > max2) {
				max2 = temp2;
			}
			if (temp2 < min2) {
				min2 = temp2;
			}
			double temp3 = (double)city[a[i][0]][a[i][1]].gdp / city[a[i][0]][a[i][1]].population;
			if (temp3 > max3) {
				max3 = temp3;
			}
			if (temp3 < min3) {
				min3 = temp3;
			}
		}
		long long kp = max1 - min1, kg = max2 - min2, kpg = max3 - min3;
		if (kp == 0)
			kp = 1;
		if (kg == 0)
			kg = 1;
		if (kpg == 0)
			kpg = 1;
		for (int i = 0; i < a.size(); i++) {
			long long pi = city[a[i][0]][a[i][1]].population, gi = city[a[i][0]][a[i][1]].gdp;
			double pgi = gi / pi;
			int temp1 = height - height * pi / kp;
			int temp2 = height - height * gi / kg;
			int temp3 = height - height * pgi / kpg;
			pxy.push_back({ startx,starty + temp1 });
			gxy.push_back({ startx,starty + temp2 });
			pgxy.push_back({ startx,starty + temp3 });
			startx += size_len;
		}
		draw(pxy, len, height);
		draw(gxy, len, height);
		draw(pgxy, len, height);
	}
	void compare_year() {
		cout << "请输入要分析的城市名称：" << endl;
		string n;
		cin >> n;
		vector<vector<int>>city_year;
		check_city_year(city_year, n);
		if (city_year.empty()) {
			cout << "该城市不存在" << endl;
			return;
		}
		long long p = 0, g = 0;
		double pg = 0, percent_p = 0, percent_g = 0, percent_pg = 0;
		int size = city_year.size();
		for (int i = 0; i < size; i++) {
			check_city(city_year[i][0], n);
		}
		for (int i = 0; i < size - 1; i++) {
			p += city[city_year[i + 1][0]][city_year[i + 1][1]].population - city[city_year[i][0]][city_year[i][1]].population;
			g += city[city_year[i + 1][0]][city_year[i + 1][1]].gdp - city[city_year[i][0]][city_year[i][1]].gdp;
			pg += city[city_year[i + 1][0]][city_year[i + 1][1]].gdp / city[city_year[i + 1][0]][city_year[i + 1][1]].population - city[city_year[i][0]][city_year[i][1]].gdp / city[city_year[i][0]][city_year[i][1]].population;
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
		while (!(cin >> n) || (n != 0 && (n < 1980 || n>2026))) {
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
		cout << "请输入年份" << endl;
		y = valid_year();
		while(1){
			City c;
			int z = 0;
			cout << "按1输入城市数据，按0退出";
			cin >> z;
			if (z == 0) {
				break;
			}
			c.setcity(y);
			city[y].push_back(c);
		}
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
				city[y].erase(city[y].begin() + i);
				cout << "已删除" << endl;
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
		cout << "请输入城市名" << endl;
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

long long City::total_gdp = 0, City::total_population = 0;
int main() {
	Operate op;
	int choice;
	while (true) {
		cout << "\n====== 城市GDP管理系统 ======\n";
		cout << "1. 添加城市数据\n";
		cout << "2. 查询年份统计\n";
		cout << "3. 查询单个城市信息\n";
		cout << "4. 删除指定年份\n";
		cout << "5. 删除指定城市\n";
		cout << "6. 清空所有数据\n";
		cout << "7. 同年份两城市对比\n";
		cout << "8. 单城市跨年份趋势分析\n";
		cout << "9. 查看数据可视化图表\n";
		cout << "0. 退出系统\n";
		cout << "请输入操作：";
		cin >> choice;

		switch (choice) {
		case 1: {
			op.add();
			break;
		}
		case 2: {
			op.check_year();
			break;
		}
		case 3: {
			op.check_city();
			break;
		}
		case 4: {
			op.delete_year();
			break;
		}
		case 5: {
			op.delete_city();
			break;
		}
		case 6: {
			op.delete_all();
			break;
		}
		case 7: {
			op.compare_city();
			break;
		}
		case 8: {
			op.compare_year();
			break;
		}
		case 9: {
			cout << "请输入城市名：";
			string name;
			cin >> name;
			vector<vector<int>> arr;
			op.check_city_year(arr, name);
			if (arr.empty()) cout << "城市不存在！\n";
			else op.map_year(arr, 0);
			break;
		}
		case 0: {
			cout << "已退出系统\n";
			return 0;
		}
		default: {
			cout << "输入无效！\n";
			break;
		}
		}
	}
}