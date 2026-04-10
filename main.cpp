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
void clear_screen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
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
	friend class File_operate;
	long long valid_input() {//校验输入合法性
		long long n;
		while (!(cin >> n) || n <= 0) {
			cout << "请输入合法数据" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		return n;
	}
	void setcity(int y,bool over,string name_set="") {//输入数据
		if (over) {
			total_gdp -= gdp;
			total_population -= population;
		}
		string n;
		if(name_set.empty()){
			cout << "请输入城市名称：";
			cin >> n;
		}
		else {
			n = name_set;
		}
		cout << "请输入人口：";
		long long p = valid_input();
		cout << "请输入GDP：";
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
	static map<int, vector<City>>city;
public:
	friend class City;
	friend class File_operate;
	void save_data();
	void load_data();
	static int valid_int(int min, int max) {
		int n;
		while (!(cin >> n) || n < min || n > max) {
			cout << "请进行合法操作（输入 " << min << "-" << max << "）" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		return n;
	}
	static bool cmp_p1(City& a, City& b) { //按人口升序
		return a.population < b.population;
	}
	static bool cmp_p2(City& a, City& b) { //按人口降序
		return a.population > b.population;
	}
	static bool cmp_g1(City& a, City& b) { //按GDP升序
		return a.gdp < b.gdp;
	}
	static bool cmp_g2(City& a, City& b) { //按GDP降序
		return a.gdp > b.gdp;
	}
	static bool cmp_pg1(City& a, City& b) { //按人均GDP升序
		return (double)a.gdp / a.population < (double)b.gdp / b.population;
	}
	static bool cmp_pg2(City& a, City& b) { //按人均GDP降序
		return (double)a.gdp / a.population > (double)b.gdp / b.population;
	}
	void sorting() {
		int k;
		cout << "请输入年份：（按0退出）";
		k = valid_check_year();
		if (k == 0) {
			return;
		}
		cout << "请选择升序或降序：（升序按1，降序按2）";
		int x = valid_int(1,2);
		cout << "\n请选择排序数据：";
		int y = valid_int(1,3);
		if (x == 2) {
			if (y == 1) {
				sort(city[k].begin(), city[k].end(), cmp_p2);
			}
			if (y == 2) {
				sort(city[k].begin(), city[k].end(), cmp_g2);
			}
			if (y==3) {
				sort(city[k].begin(), city[k].end(), cmp_pg2);
			}
		}
		else {
			if (y == 1) {
				sort(city[k].begin(), city[k].end(), cmp_p1);
			}
			if (y == 2) {
				sort(city[k].begin(), city[k].end(), cmp_g1);
			}
			if (y == 3) {
				sort(city[k].begin(), city[k].end(), cmp_pg1);
			}
		}
		cout << "====== 城市列表 ======" << endl;
		cout << fixed << setprecision(2);
		for (int i = 0; i < city[k].size(); i++) {
			cout << i + 1 << ". " << city[k][i].name
				<< " 人口：" << city[k][i].population
				<< " GDP：" << city[k][i].gdp
				<< " 人均GDP：" << (double)city[k][i].gdp / city[k][i].population << endl;
		}
		return;
	}
	void sorting(int k) {
		cout << "请选择升序或降序：（升序按1，降序按2）";
		int x = valid_int(1, 2);
		cout << "\n请选择排序数据：";
		int y = valid_int(1, 3);
		if (k == 0) {
			return;
		}
		if (x == 2) {
			if (y == 1) {
				sort(city[k].begin(), city[k].end(), cmp_p2);
			}
			if (y == 2) {
				sort(city[k].begin(), city[k].end(), cmp_g2);
			}
			if (y == 3) {
				sort(city[k].begin(), city[k].end(), cmp_pg2);
			}
		}
		else {
			if (y == 1) {
				sort(city[k].begin(), city[k].end(), cmp_p1);
			}
			if (y == 2) {
				sort(city[k].begin(), city[k].end(), cmp_g1);
			}
			if (y == 3) {
				sort(city[k].begin(), city[k].end(), cmp_pg1);
			}
		}
		cout << "====== 城市列表 ======" << endl;
		cout << fixed << setprecision(2);
		for (int i = 0; i < city[k].size(); i++) {
			cout << i + 1 << ". " << city[k][i].name
				<< " 人口：" << city[k][i].population
				<< " GDP：" << city[k][i].gdp
				<< " 人均GDP：" << (double)city[k][i].gdp / city[k][i].population << endl;
		}
		return;
	}
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
						cout << "●";
						z = 1;
						break;
					}
				}
				if (!z) cout << ".";
			}
			cout << endl;
		}
	}
	void map_year(vector<vector<int>>& a, int y) {
		if (a.size() < 2) {
			cout << "该城市数据不足2年，无法生成趋势图" << endl;
			return;
		}
		int len = 40;
		int height = 10;
		int size_len = len / a.size();
		if (size_len == 0) size_len = 1;
		vector<vector<int>>pxy, gxy, pgxy;
		int startx = 1;
		int starty = 0;
		long long max1 = LLONG_MIN, min1 = LLONG_MAX;
		long long max2 = LLONG_MIN, min2 = LLONG_MAX;
		double max3 = -1e18, min3 = 1e18;
		for (int i = 0; i < a.size(); i++) {
			long long temp1 = city[a[i][0]][a[i][1]].population;
			long long temp2 = city[a[i][0]][a[i][1]].gdp;
			double temp3 = (double)city[a[i][0]][a[i][1]].gdp / city[a[i][0]][a[i][1]].population;

			max1 = max(max1, temp1); min1 = min(min1, temp1);
			max2 = max(max2, temp2); min2 = min(min2, temp2);
			max3 = max(max3, temp3); min3 = min(min3, temp3);
		}

		long long kp = max1 - min1; if (kp == 0) kp = 1;
		long long kg = max2 - min2; if (kg == 0) kg = 1;
		double kpg = max3 - min3; if (kpg == 0) kpg = 1;

		for (int i = 0; i < a.size(); i++) {
			long long pi = city[a[i][0]][a[i][1]].population;
			long long gi = city[a[i][0]][a[i][1]].gdp;
			double pgi = (double)gi / pi;

			int temp1 = height - 1 - (int)((height - 1) * (double)(pi - min1) / kp);
			int temp2 = height - 1 - (int)((height - 1) * (double)(gi - min2) / kg);
			int temp3 = height - 1 - (int)((height - 1) * (pgi - min3) / kpg);

			pxy.push_back({ startx, starty + temp1 });
			gxy.push_back({ startx, starty + temp2 });
			pgxy.push_back({ startx, starty + temp3 });

			startx += size_len;
		}
		cout << "\n====== 人口趋势图 ======" << endl;
		draw(pxy, len, height);
		cout << "\n====== GDP趋势图 ======" << endl;
		draw(gxy, len, height);
		cout << "\n====== 人均GDP趋势图 ======" << endl;
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
	void fix() {
		cout << "请输入年份：" << endl;
		int y;
		y = valid_check_year();
		cout << "请输入城市：" << endl;
		string c;
		cin >> c;
		bool found = false;
		int found_idx = -1;
		for (int i = 0; i < city[y].size(); i++) {
			if (city[y][i].name == c) {
				found = true;
				found_idx = i;
				break;
			}
		}
		if (found) {
			cout << "请重新输入该城市数据：" << endl;
			city[y][found_idx].setcity(y, true, c);
			cout << "修改成功" << endl;
		}
		else {
			cout << "该年份此城市数据不存在" << endl;
		}
		return;
	}
	void add_year() {//添加年份
		int y;
		cout << "请输入年份（按0退出）" << endl;
		y = valid_year();
		if (!y) {
			return;
		}
		while (1) {
			int z = 0;
			cout << "按1输入城市数据，按0退出" << endl;
			z = valid_int(0, 1);
			if (z == 0) {
				break;
			}
			cout << "请输入城市名称：";
			string n;
			cin >> n;
			bool found = false;
			int found_idx = -1;
			for (int i = 0; i < city[y].size(); i++) {
				if (city[y][i].name == n) {
					found = true;
					found_idx = i;
					break;
				}
			}
			if (found) {
				int choice = valid_int(0, 1);
				cout << "该年份此城市已存在，覆写按1，取消按0：" << endl;
				if (choice == 1) {
					city[y][found_idx].setcity(y, true, n);
					cout << "覆写成功" << endl;
				}
			}
			else {
				City c;
				c.setcity(y, false, n);
				city[y].push_back(c);
				cout << "添加成功" << endl;
			}
		}
	}
	void add_city() {
		string n;
		while (1) {
			cout << "请输入城市：";
			cin >> n;
			cout << "\n确定按1，重新输入按2，退出按0" << endl;
			int k;
			k = valid_int(0, 2);
			if (!k) {
				return;
			}
			else if (k == 1) {
				break;
			}
		}
		while (1) {
			cout << "请输入年份（按0退出）：" << endl;
			int k;
			k = valid_year();
			if (!k) {
				return;
			}
			bool found = false;
			int found_idx = -1;
			for (int i = 0; i < city[k].size(); i++) {
				if (city[k][i].name == n) {
					found = true;
					found_idx = i;
					break;
				}
			}
			if (found) {
				cout << "该年份此城市已存在，覆写请按1，取消请按0" << endl;
				int if_pass = valid_int(0, 1);
				if (if_pass == 1) {
					city[k][found_idx].setcity(k, true, n);
					cout << "覆写成功" << endl;
				}
			}
			else {
				City c;
				c.setcity(k, false, n);
				city[k].push_back(c); 
				cout << "添加成功" << endl;
			}
		}
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
		cout << "删除所有年份按1，删除某年份按2，退出按0" << endl;
		int k = valid_int(0, 2);
		if (k == 1) {
			cout << "请输入删除城市名" << endl;
			string n2;
			cin >> n2;
			int delete_count = 0;
			for (auto& year_item : city) {
				int year = year_item.first;
				auto& city_list = year_item.second;
				for (int i = 0; i < city_list.size(); i++) {
					if (city_list[i].name == n2) {
						City::total_gdp -= city_list[i].gdp;
						City::total_population -= city_list[i].population;
						city_list.erase(city_list.begin() + i);
						delete_count++;
						i--; 
					}
				}
			}
			if (delete_count > 0) {
				cout << "已删除所有年份的 [" << n2 << "]，共删除 " << delete_count << " 条数据" << endl;
			}
			else {
				cout << "该城市不存在任何数据" << endl;
			}
			return;
		}
		if (k == 0) {
			return;
		}
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
		int k;
		cout << "查询各城市详情按1，退出按0" << endl;
		k = valid_int(0, 1);
		if(k)
		    sorting(y);
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
class File_operate {
public:
	void save(map<int,vector<City>>& c) {
		ofstream File("city.txt");
		if (!File.is_open()) {
			cout << "文件打开失败，保存失败！" << endl;
			return;
		}
		File << c.size() << endl;
		for (auto& i : c) {
			int year = i.first;
			vector<City>& cities = i.second;
			File << year << " " << cities.size() << endl;
			for (int k = 0; k < cities.size(); k++) {
				File << cities[k].year << " " << cities[k].name << " " << cities[k].population << " " << cities[k].gdp << endl;
			}
		}
		File.close();
		cout << "数据保存成功！（文件名：city.txt）" << endl;
	}
	void load(map<int, vector<City>>& c, long long& total_gdp, long long& total_population) {
		ifstream File("city.txt");
		if (!File.is_open()) {
			cout << "文件打开失败" << endl;
			return;
		}
		c.clear();
		total_gdp = 0;
		total_population = 0;
		int total_years;
		File >> total_years;
		for (int i = 0; i < total_years; i++) {
			int year, city_count;
			File >> year >> city_count;
			for (int j = 0; j < city_count; j++) {
				City city;
				File >> city.year >> city.name >> city.population >> city.gdp;
				c[year].push_back(city);
				total_gdp += city.gdp;
				total_population += city.population;
			}
		}
		File.close();
		cout << "数据加载成功" << endl;
	}
};
long long City::total_gdp = 0, City::total_population = 0;
void Operate::save_data() {
	File_operate fo;
	fo.save(city);
}
void Operate::load_data() {
	File_operate fo;
	fo.load(city, City::total_gdp, City::total_population);
}
class Menu {
public:
	// ==================== 子菜单：数据管理 ====================
	void menu_data_manage(Operate& op) {
		while (true) {
			clear_screen();
			cout << "\n====== 数据管理 ======\n";
			cout << "1. 添加城市数据\n";
			cout << "2. 删除指定年份\n";
			cout << "3. 删除指定城市\n";
			cout << "4. 清空所有数据\n";
			cout << "5. 修改城市数据\n";
			cout << "0. 返回主菜单\n";
			int choice = op.valid_int(0, 4);

			clear_screen();
			switch (choice) {
			case 1: op.add_year(); break;
			case 2: op.delete_year(); break;
			case 3: op.delete_city(); break;
			case 4: op.delete_all(); break;
			case 5: op.fix(); break;
			case 0: return;
			}
			cout << "\n按回车键继续...";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get();
		}
	}
	// ==================== 子菜单：查询分析 ====================
	void menu_query_analyze(Operate& op) {
		while (true) {
			clear_screen();
			cout << "\n====== 查询分析 ======\n";
			cout << "1. 查询年份统计（含临时排序）\n";
			cout << "2. 查询单个城市信息\n";
			cout << "3. 同年份两城市对比\n";
			cout << "4. 单城市跨年份趋势分析\n";
			cout << "5. 查看数据可视化图表\n";
			cout << "6. 城市数据排序（永久生效）\n";
			cout << "0. 返回主菜单\n";
			int choice = op.valid_int(0, 6);

			clear_screen();
			switch (choice) {
			case 1: op.check_year(); break;
			case 2: op.check_city(); break;
			case 3: op.compare_city(); break;
			case 4: op.compare_year(); break;
			case 5: {
				cout << "请输入城市名：";
				string name;
				cin >> name;
				vector<vector<int>> arr;
				op.check_city_year(arr, name);
				if (arr.empty()) cout << "城市不存在！\n";
				else op.map_year(arr, 0);
				break;
			}
			case 6: op.sorting(); break;
			case 0: return;
			}
			cout << "\n按回车键继续...";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get();
		}
	}
};
map<int, vector<City>> Operate::city;
int main() {
	Operate op;
	op.load_data();
	Menu menu;
	while (true) {
		clear_screen();
		cout << "\n======   城市GDP管理系统   ======\n";
		cout << "1.数据管理\n";
		cout << "2.查询分析\n";
		cout << "3.手动保存数据\n";
		cout << "0.退出系统（自动保存）\n";
		int choice = op.valid_int(0, 3);

		if (choice == 0) {
			clear_screen();
			cout << "正在自动保存数据...";
			op.save_data();
			cout << "\n已退出系统，欢迎下次使用！" << endl;
			return 0;
		}

		switch (choice) {
		case 1: menu.menu_data_manage(op); break;
		case 2: menu.menu_query_analyze(op); break;
		case 3: {
			clear_screen();
			op.save_data();
			cout << "\n按回车键继续...";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.get();
			break;
		}
		}
	}
}