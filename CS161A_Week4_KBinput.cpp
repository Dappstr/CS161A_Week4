/*
* Created 07/22/2021
* Project for CS161A to allow for program exit on keyboard input instead of implicit data input
* In order to get automatic keyboard input, we create a new thread which uses GetAsyncKeyState in order to continuously monitor input
* The reason we need to create a new thread is because the 'cin' function is hijacking keyboard input which stops GetAsyncKeyState from grabbing input
*/

#include <iostream>
#include <Windows.h> //This is an OS-Specific library and is not compatible on OSX, Linux, or other non-Windows opeating systems :(

//This is just to declare that when we use cout and cin that we will be using them from the standard library
using std::cout; using std::cin;

/*
Function to declare at the start of our program that we will have a checkEsc function and that checkEsc will return a DWORD,
and the function that will call our checkEsc function which will be CreateThread() requires the use of a pointer to the __stdcall convention
therefor we give checkEsc the WINAPI convention which expands checkEsc's convention specifier
 */
DWORD WINAPI checkEsc(LPVOID lParam)
{
    /*
    GetAsyncKeyState is a function that will check for the status of whether or not a key is pressed
    We put this in a while loop to continuously check for the state of the key
    The 0 value in booleans is used to represent false.
    This means that while GetAsyncKeyState receives a FALSE state for the Escape key, it will continue to run
    If we were to change the while argument to == 1, the program would exit because we would be changing the value of GetAsyncKeyState to true
    even if we are not pressing the key ourselves.
    */
    while (GetAsyncKeyState(VK_ESCAPE) == 0)
    {
        //Sleep in order to avoid any unusual issues that may come with immediate exiting
        Sleep(5);
    }
    //Program exits
    exit(0);
}

void tempConversion()
{
    double inputTemp, outputTemp;

    cout << "Enter temperature in Fahrenheit: ";
    cin >> inputTemp;

    outputTemp = (5 * (inputTemp - 32)) / 9;

    cout << "\nThe current temperature in celsius is: "
        << outputTemp << std::endl;

    //Infinite loop that will run until user presses Escape
    while (true)
    {
        cout << "\nPlease enter temperature in Fahrenheit or press 'Esc' to exit: ";
        cin >> inputTemp;

        outputTemp = (5 * (inputTemp - 32)) / 9;

        cout << "\nThe current temperature in celsius is: "
            << outputTemp << std::endl;
    }
}


int main()
{
    /*
    We create our thread at the start of our main function to initialize the check for the Escape key  which will be used as our key to exit the program.
    Since CreateThread takes in multiple arguments, we satisfy this requirement by giving the required values separated by commas
    */
    CreateThread(NULL, 0, checkEsc, NULL, 0, NULL);

    cout << "---------------------------------\n";
    cout << "\tFahrenheit to Celsius Conversion App\n";
    cout << "---------------------------------\n";

    tempConversion();

    return 0;
}