#include <iostream>
#include <array>
#include <memory>
#include <string_view>
#include <map>

#include "speech.h"

template <typename T> // Function template prototype
T larger(T a, T b);

int main(int, char **)
{
    std::cout << "Hello, from basic_hello!\n";
    std::cout << get_phrase() << std::endl;

    double a{1.5}, b{}, c{};
    double result{a / b};
    std::cout << a << "/" << b << " = " << result << std::endl;
    std::cout << result << " + " << a << " = " << result + a << std::endl;
    result = b / c;
    std::cout << b << "/" << c << " = " << result << std::endl;

    enum class Day
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    Day yesterday{Day::Monday}, today{Day::Tuesday}, tomorrow{Day::Wednesday};

    using BigOnes = unsigned long long;
    BigOnes mynum{};

    int values[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int size = std::size(values);
    std::cout << "Size: " << size << std::endl;

    double carrots[3][4]{
        {2.5, 3.2, 3.7, 4.1}, // First row
        {4.1, 3.9, 1.6, 3.5}, // Second row
        {2.8, 2.3, 0.9, 1.1}, // Third row
    };

    std::array<double, 4> these{1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> those{1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> them{1.0, 1.0, 5.0, 5.0};

    if (these == those)
        std::cout << "these and those are equal." << std::endl;
    if (those != them)
        std::cout << "those and them are not equal." << std::endl;
    if (those > them)
        std::cout << "those are greater than them." << std::endl;
    if (them < those)
        std::cout << "them are less than those." << std::endl;

    long *pnumber{nullptr};

    std::unique_ptr<double> pdata{std::make_unique<double>(999.0)};
    // Or using Auto
    auto pdata2{std::make_unique<double>(999.0)};

    *pdata = 8888.0;
    std::cout << *pdata << std::endl; // Outputs 8888

    double data{3.5};

    // Chap 6 pg 214
    // A const pointer containing the address of data
    double *const pdata3{&data};

    // This memory the ref is pointing is constant. You can't change the data
    // using a constant reference.
    const double &const_ref{data};
    // const_ref *= 2; // Illegal attempt to modify data through a reference-to-const

    std::cout << "Larger of 1.5 and 2.5 is " << larger(1.5, 2.5) << std::endl;

    std::map<std::string, size_t> animal_population{
        {"humans",
         7000000000},
        {"chickens", 17863376000},
        {"camels",
         24246291},
        {"sheep",
         1086881528},
    };

    for (const auto &[species, count] : animal_population)
    {
        std::cout << "There are " << count << " " << species
                  << " on this planet.\n";
    }
}

// Using reference we can specify the array size.
// The extra parentheses surrounding &array are required.
// Without them, the compiler would no longer interpret the parameter type as a
// reference to an array of doubles but as an array of references to double.
double average10(const double (&array)[10]) // Only arrays of length 10 can be passed!
{
    double sum{};
    // Accumulate total in here
    for (size_t i{}; i < 10; ++i)
        sum += array[i];
    // Sum array elements
    return sum / 10;
    // Return average
}

// Because arrays of references are not allowed in C++, this would then result
// in a compiler error:
// double average10(const double& array[10]) // error: array of double& is not allowed

// You have already seen a more modern alternative to working with arrays of fixed length in Chapter 5:
// std::array<>. Using values of this type, you can just as safely pass fixed-size arrays by reference and without
// having to remember the tricky syntax for passing plain fixed-size arrays by reference:
double average11(const std::array<double, 11> &values) { return 0; }

// Chap 8 pg 281
// Always use the type std::string_view instead of const std::string& for input string parameters.
// While there is nothing wrong with using const std::string_view&, you might as well pass std::string_view
// by value because copying these objects is cheap.
// The compiler, however, will refuse any and all implicit conversions of std::string_view objects
// to values of type std::string (give it a try!). The rationale behind this deliberate restriction is that you
// normally use string_view to avoid more expensive string copy operations, and converting a string_view
// back to a std::string always involves copying the underlying character array. To protect you from
// accidentally doing so, the compiler is not allowed to ever implicitly make this conversion. You always have to
// explicitly add the conversion in this direction yourself.

void show_error(std::string_view message = "Program Error")
{
}

// Note: Chap 8 "Return type deduction" and the gotcha's associated
// Caution auto never deduces to a reference type, always to a value type. This implies that even when
// you assign a reference to auto, the value still gets copied. This copy will moreover not be const, unless you
// explicitly use const auto. To have the compiler deduce a reference type, you can use auto& or const auto&.

// Chap 8 pg 294 Optionals

// Templates
template <typename T>
T larger(T a, T b)
{
    return a > b ? a : b;
}

// See "Function Template Specialization" Pg 323

// Using the explicit Keyword Pg 394
// A problem with class constructors with a single parameter is that the compiler can use such a constructor as
// an implicit conversion from the type of the parameter to the class type.
// Basically the compiler may attempt to convert a number into a class if you
// do something like this:
// if (box1.hasLargerVolumeThan(50.0))
// You should use: if (box1.hasLargerVolumeThan(Box{50.0}))
// OR
// Use the explicit keyword: explicit Cube(double aSide);

// Exceptions:
// The golden rule for exceptions is to always throw by value and catch by reference (reference-to-const,
// normally). In other words, you mustn’t throw a new’ed exception (and definitely no pointer to a local object), nor
// should you ever catch an exception object by value. Obviously, catching by value would result in a redundant
// copy, but that’s not the worst of it. Catching by value may slice off parts of the exception object! The reason this
// is so important is that exception slicing might just slice off precisely that valuable piece of information that you
// need to diagnose which error occurred and why!

// Move semantics
// template <typename T>
// class Array
// {
// private:
//  T* elements; // Array of type T
//  size_t size; // Number of array elements
// public:
//  explicit Array(size_t arraySize);// Constructor
//  Array(const Array& array); // Copy constructor
//  Array(Array&& array); // Move constructor
//  ~Array();// Destructor
//  Array& operator=(const Array& rhs);// Copy assignment operator
//  T& operator[](size_t index); // Subscript operator
//  const T& operator[](size_t index) const; // Subscript operator-const arrays
//  size_t getSize() const noexcept { return size; } // Accessor for size
//  void swap(Array& other) noexcept;// noexcept swap function
// };

// Heirarchies
// weak pointers are good for cylic structures.
// A child node doesn't want to take ownership of a parent Node, it just
// want to use it. We need the weak pointer because a parent-child relationship
// create a circular reference scenario. In return the child should always
// check if the parent pointer is still valid using weak pointer methods.

// Important rules when using shared_from_this()

// Never call it in constructors: The object must already be managed by a shared_ptr before you can call shared_from_this().
// Only call it on objects managed by shared_ptr: If you call shared_from_this() on an object not owned by a shared_ptr, it will throw a std::bad_weak_ptr exception.
// Always use factory methods: To ensure proper initialization, it's often best to create objects with factory methods:

// #include <memory>
// #include <vector>
// #include <iostream>

// class Node : public std::enable_shared_from_this<Node> {
// private:
//     std::string name;
//     std::weak_ptr<Node> parent;  // Weak reference up
//     std::vector<std::shared_ptr<Node>> children;  // Strong references down

// public:
//     Node(const std::string& nodeName) : name(nodeName) {}

//     void addChild(std::shared_ptr<Node> child) {
//         child->parent = shared_from_this();  // Create shared_ptr to this
//         children.push_back(std::move(child));
//     }

//     void printParent() {
//         if (auto p = parent.lock()) {
//             std::cout << name << "'s parent is " << p->getName() << std::endl;
//         } else {
//             std::cout << name << " has no parent (or parent was deleted)" << std::endl;
//         }
//     }

//     std::string getName() const { return name; }
// };

// ---------Factory methods ---------------------------
// class Node : public std::enable_shared_from_this<Node> {
//     public:
//         // Factory method ensuring proper shared_ptr management
//         static std::shared_ptr<Node> create(const std::string& name) {
//             return std::shared_ptr<Node>(new Node(name));
//         }

//     private:
//         // Make constructor private to enforce factory method usage
//         Node(const std::string& name) : name(name) {}
//         // ... rest of the class
//     };
