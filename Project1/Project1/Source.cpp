#include <iostream>
using namespace std;

#include <iostream>
using namespace std;

template <typename T>
class Queue {
public:
	Queue() {
		size_ = 0;
		capacity_ = 10; // начальная емкость
		arr_ = new T[capacity_];
	}

	~Queue() {
		delete[] arr_;
	}

	void AddElement(T el) {
		if (size_ == capacity_) { // Проверяем, нужно ли увеличить емкость
			Resize(capacity_ * 2);
		}
		arr_[size_] = el; // Добавляем элемент в конец очереди
		size_++;
	}

	void DeleteElement() {
		if (size_ == 0) {
			return; // ничего не делаем, если очередь пуста
		}
		for (size_t i = 0; i < size_ - 1; ++i) {
			arr_[i] = arr_[i + 1]; // Сдвигаем все элементы на один влево
		}
		size_--;


		if (size_ < capacity_ / 4 && capacity_ > 10) { // Можно уменьшить емкость, если элементов стало мало
			Resize(capacity_ / 2);
		}
	}

	size_t GetSize() const {
		return size_;
	}
	T GetElement(int n) {
		return arr_[n];
	}

	void Print() {
		for (size_t i = 0; i < size_; ++i) {
			cout << arr_[i] << ' ';
		}
		cout << endl;
	}
	void Resize(size_t new_capacity) {
		T* new_arr = new T[new_capacity];
		for (size_t i = 0; i < size_; ++i) {
			new_arr[i] = arr_[i];
		}
		delete[] arr_;
		arr_ = new_arr;
		capacity_ = new_capacity;
	}
private:
	T* arr_;
	size_t size_;
	size_t capacity_;
};

class Interface {
public:
	Interface() = default;
	Interface(double price, double min_multiple, double max_multiple)
		: price_(price), min_multiple_(min_multiple), max_multiple_(max_multiple) {
	}

	virtual void Print() const = 0;

	double GetPrice() const {
		return price_;
	}
	void SetPrice(double price) {
		price_ = price;
	}

	double GetMinMultiple() const {
		return min_multiple_;
	}
	void SetMinMultiple(double min_multiple) {
		min_multiple_ = min_multiple;
	}

	double GetMaxMultiple() const {
		return max_multiple_;
	}
	void SetMaxMultiple(double max_multiple) {
		max_multiple_ = max_multiple;
	}
protected:
	double price_;
	double min_multiple_;
	double max_multiple_;
};

class LaboratoryOptics : public Interface {
public:
	LaboratoryOptics() = default;
	LaboratoryOptics(double price, double min_multiple, double max_multiple, bool direct_correction_to_pc)
		: Interface(price, min_multiple, max_multiple), direct_correction_to_pc_(direct_correction_to_pc) {
	}

	bool GetDirectConnection() const {
		return direct_correction_to_pc_;
	}
	void SetDirectConnection(bool direct_correction_to_pc) {
		direct_correction_to_pc_ = direct_correction_to_pc;
	}
protected:
	bool direct_correction_to_pc_;
};

class Telescope : public LaboratoryOptics {
public:
	Telescope() = default;
	Telescope(double price, double min_multiple, double max_multiple, bool direct_correction_to_pc, bool star_scaner)
		: LaboratoryOptics(price, min_multiple, max_multiple, direct_correction_to_pc), star_scaner_(star_scaner) {
	}

	bool GetStarScaner() const {
		return star_scaner_;
	}
	void SetStarScanerP(bool star_scaner) {
		star_scaner_ = star_scaner;
	}

	void Print() const override {
		cout << "Телескоп." << endl;
		cout << "Кратность от " << min_multiple_ << " до " << max_multiple_ << endl;
		cout << "Цена: " << price_ << endl;
		if (star_scaner_) {
			cout << "Сканер звезд встроен." << endl;
		}
		else {
			cout << "Сканер звезд не встроен." << endl;
		}
		cout << endl;
	}
private:
	bool star_scaner_;
};

class Microscope : public LaboratoryOptics {
public:
	Microscope() = default;
	Microscope(double price, double min_multiple, double max_multiple, bool direct_correction_to_pc, int number_of_microlenses)
		: LaboratoryOptics(price, min_multiple, max_multiple, direct_correction_to_pc), number_of_microlenses_(number_of_microlenses) {
	}

	int GetNumberOfMicrolenses() const {
		return number_of_microlenses_;
	}
	void SetNumberOfMicrolenses(int number_of_microlenses) {
		number_of_microlenses_ = number_of_microlenses;
	}

	void Print() const override {
		cout << "Микроскоп." << endl;
		cout << "Кратность от " << min_multiple_ << " до " << max_multiple_ << endl;
		cout << "Цена: " << price_ << endl;
		cout << "Количество микролинз: " << number_of_microlenses_ << endl;
		cout << endl;
	}
private:
	int number_of_microlenses_;
};

class OpticalDevices : public Interface {
public:
	OpticalDevices() = default;
	OpticalDevices(double price, double min_multiple, double max_multiple, const string& grid_color)
		: Interface(price, min_multiple, max_multiple), grid_color_(grid_color) {
	}

	string GetGridColor() const {
		return grid_color_;
	}
	void SetGridColor(const string& grid_color) {
		grid_color_ = grid_color;
	}
protected:
	string grid_color_;
};

class TwoEyedOpticalDevices : public OpticalDevices {
public:
	TwoEyedOpticalDevices() = default;
	TwoEyedOpticalDevices(double price, double min_multiple, double max_multiple, const string& grid_color, const string& appointment)
		: OpticalDevices(price, min_multiple, max_multiple, grid_color), appointment_(appointment) {
	}

	string GetAppointment() const {
		return appointment_;
	}
	void SetAppointment(const string& appointment) {
		appointment_ = appointment;
	}
protected:
	string appointment_;
};

class OneEyedOpticalDevices : public OpticalDevices {
public:
	OneEyedOpticalDevices() = default;
	OneEyedOpticalDevices(double price, double min_multiple, double max_multiple, const string& grid_color)
		: OpticalDevices(price, min_multiple, max_multiple, grid_color) {
	}
};

class Binoculars : public TwoEyedOpticalDevices {
public:
	Binoculars() = default;
	Binoculars(double price, double min_multiple, double max_multiple, const string& grid_color, const string& appointment)
		: TwoEyedOpticalDevices(price, min_multiple, max_multiple, grid_color, appointment) {
	}

	void Print() const override {
		cout << "Бинокль." << endl;
		cout << "Кратность от " << min_multiple_ << " до " << max_multiple_ << endl;
		cout << "Цена: " << price_ << endl;
		cout << "Цвет сетки: " << grid_color_ << endl;
		cout << "Назначение: " << appointment_ << endl;
		cout << endl;
	}
};

class Monocular : public OneEyedOpticalDevices {
public:
	Monocular() = default;
	Monocular(double price, double min_multiple, double max_multiple, const string& grid_color, const string& fastening)
		: OneEyedOpticalDevices(price, min_multiple, max_multiple, grid_color), fastening_(fastening) {
	}

	string GetFastening() const {
		return fastening_;
	}
	void SetFastening(const string& fastening) {
		fastening_ = fastening;
	}

	void Print() const override {
		cout << "Монокуляр." << endl;
		cout << "Кратность от " << min_multiple_ << " до " << max_multiple_ << endl;
		cout << "Цена: " << price_ << endl;
		cout << "Цвет сетки: " << grid_color_ << endl;
		cout << "Крепление: " << fastening_ << endl;
		cout << endl;
	}
private:
	string fastening_;
};

class OpticalSight : public OneEyedOpticalDevices {
public:
	OpticalSight() = default;
	OpticalSight(double price, double min_multiple, double max_multiple, const string& grid_color)
		: OneEyedOpticalDevices(price, min_multiple, max_multiple, grid_color) {
	}

	void Print() const override {
		cout << "Оптический прицел." << endl;
		cout << "Кратность от " << min_multiple_ << " до " << max_multiple_ << endl;
		cout << "Цена: " << price_ << endl;
		cout << "Цвет сетки: " << grid_color_ << endl;
		cout << endl;
	}
};

void showMainMenu() {
	 // Очистка консоли (для Windows)
	cout << " _----------------------------------------------------------------_" << endl;
	cout << "|                           ГЛАВНОЕ МЕНЮ                           |" << endl;
	cout << "| 1. Опция 1                                                       |" << endl;
	cout << "| 2. Опция 2                                                       |" << endl;
	cout << "| 3. Опция 3                                                       |" << endl;
	cout << "| 0. Выход                                                         |" << endl;
	cout << " -________________________________________________________________-" << endl;
	cout << " Выберите пункт меню: ";
}

int main() {
	setlocale(LC_ALL, "rus");
	/*cout << " _----------------------------------------------------------------_" << endl;
	cout << "| ------------------------- ГЛАВНОЕ МЕНЮ ------------------------- |" << endl;*/
	Queue<Interface*> queue;
	bool flag = true;
	OpticalSight el(12000, 1, 4, "red");
	queue.AddElement(el);
	while (flag) {
		showMainMenu();
		int choice;
		cin >> choice;

		switch (choice) {
		case 0:
			system("cls");
			cout << "Выход...\n";
			flag = false;  // Меняем флаг, цикл завершится на следующей итерации
			break;  // Тоже прерывает только switch
		case 1:
			system("cls");
			cout << "Работаем...\n";
			break;  //  Прерывает только switch, цикл продолжается!
		case 2:
			system("cls");
			cout << "Дважды Работаем...\n";
			break;  //  Прерывает только switch, цикл продолжается!
		default:
			cout << "Ошибка!\n";
			break;
		}

		cout << "Эта строка выполняется после switch.\n";  // Управление приходит сюда
	}

	cout << "Программа завершена.\n";
	return 0;
}