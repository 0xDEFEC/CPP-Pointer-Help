/*

	ptrGuide.cpp : This is detailed a file aimed to help those new to C++ get a better understanding of the multiple
				  usages of pointers. It includes the following:
										- Referencing:                        ( & )
										- Dereferencing:                      ( * )
										- Use of pointers in function params: ( type func_name(int *param1) )
										- Function Pointers:                  ( typedef return_type(*type_name)(int *param1, int *param2) )
				  I know these may seem intimidating at first--and they were for me--but below I will try my best to
				  explain what these do and when they are used in practical application. :)

*/

// definitions of functions used in examples - can be viewed all the way below.
int function1(int arg); void function1_ref(int& arg);
int function2(int* arg);
void function3(int(*fn)(int, int)); int callback(int arg1, int arg2);

// This is where all examples will be given because, you know, the C++ standard requires an entry point somewhere. ¯\_(ツ)_/¯
int main() {

	/* Referencing time!
		  In C++, referencing is often used when you wish to alter a variable's value by REFERENCE. This means you alter the value held
		  by the variable at its memory address. This is useful when you wish to pass values to functions and have the original variable
		  value altered, rather than the copy that would usually be passed to a function be altered.

		  Below are some examples:
	*/
	int param1 = 1; // simple arg var
	int result;     // stores function return value
		  // function1(int arg)
	result = function1(param1); /* ------> What this does is pass a copy of param1 to function1(), rather than the actual variable itself.
										   This function takes the value and adds five to it. If you print param1 after calling this function,
										   it would still equal 1. This is because a copy of param1 was passed, rather than the actual variable.
										   Let's say we wanted to actually modify the variable directly in the function itself, rather
										   than its copy. See below:                                                                              */
										   // function1_ref(int &arg)
	function1_ref(param1); /* ------> What this does is pass the memory address of the original variable and allows for its value to be
									  modified directly. No copies are passed as the argument since this function takes an argument of
									  (int&). This function doesn't return any value either since param1 is now increased by 5 directly.
									  If you print param1 after calling this, its value will be changed.                                          */



									  /* Dereferencing time!
											Usually when talking about dereferencing, it means referring to the value stored at a variable's address. Though, you will see the (*)
											symbol passed around a lot in C++ to define pointers. Pointers are often defined as (type(*) name). Pointer MUST be initialized. Pointers can
											be used for the same purpose as referencing, but are much less safe and have many more pro's:
												  - A pointer can be re-assigned while reference cannot, and must be assigned at initialization only.
												  - Pointer can be assigned NULL directly, whereas reference cannot.
												  - Pointers can iterate over an array, we can use ++ to go to the next item that a pointer is pointing to.
												  - A pointer is a variable that holds a memory address. A reference has the same memory address as the item it references.
												  - A pointer needs to be dereferenced with * to access the memory location it points to, whereas a reference can be used directly.

											Here are some examples:
									  */
	int param2 = 5;
	int* param2_ptr = &param2; // points to param2 and holds its value
 // function2(int *arg)
	function2(&param2); /* ------> Functions that are defined with parameters that take a pointer will take a reference to a non-pointer variable.
								 What this does is practically the same as the above example with referencing. This will take the address of param
								 and modify it directly, but in a pointer-esc manner.                                                               */
	function2(param2_ptr); // ------> Basically the same as function(&param)



	/* Function pointer time!
		  Often times function pointers are used as a manner of storing exported function addresses so they can be called. Another reason to use
		  function pointers is for functions to receive "callback functions" as parameters. These can be used in a variety of situations, such as
		  the function calling the provided function pointer when a certain event happens.

		  Below are some examples:
	*/
	//  function3(int(*fn)(int, int))
	function3(callback); /* -----------> What this does is gives function3() access to the provided function callback(). Passing callback() as a
		   // callback(int, int)         parameter to function3() allows function3() to point to callback()'s address. Then, function3() will use
										 callback() however it plans to; in this case, it simply calls it with its own arguments.                    */

	// You can also define your own function pointers. This is useful when you want to export functions from DLLs.
	// In order to export a function, you need to define a type that has the same signature as the exported function.
	// You will then hold the memory address of the exported function in a variable of this type. You can then call
	// the function via this variable because it points to a function.

	// Function type definitions follow the syntax: ( typedef return_type(*name)(parameters) )      -- THE TYPE DEFINITION ***MUST*** HAVE THE																																		   
	                                                                                              //   SAME SIGNATURE AS THE EXPORTED FUNCTION
	// NOTE: this following example uses the Win32 GetProcAddress function to retrieve a function address from kernel32.dll
 // to hold void WINAPI GetNativeSystemInfo(LPSYSTEM_INFO lpSystemInfo) located in kernel32.dll
	typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
	PGNSI function; // variable that contains the same signature as the desired exported function
	function = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo"); /* gets base address of GetNativeSystemInfo from kernel32.dll,
																									   casts it to the defined type definition, and stores it in
																									   our variable (PGNSI)function. (excuse the C-style cast)   */
																									   // Once the address is retrieved, it can be used like a normal function.
	function( /* args_here */); // call normally now that it stores the address of the exported function
}

/* End time!
	  I created this guide at, like, 6 AM. So, if it is a bit lacking, excuse my tiredness. ¯\_(ツ)_/¯
	  If there are any concepts I forgot to add, let me know. I purposely left out the extent that
	  you can take passed pointers to - i.e. iterating values, re-initializing, etc. These are the
	  fundamentals, and with those, you can learn those things easier.

	  I wasn't worried about this actually being able to compile, so it might not, but it shows you
	  different isolated scenarios to use these concepts, and that is what matters.

	  I don't believe there are any errors in this, based on a quick run-dwon in VS.
*/








/*

	Functions used in the examples above are defined down here.

*/

// takes one int arg, increments it, returns the newly modifed value
int function1(int arg) {
	arg += 5; // increase arg by 5 -> arg = arg + 5
	return arg; // return the newly modified arg
} void function1_ref(int& arg) {
	arg += 5; // increase arg by 5 -> arg = arg + 5
}

// takes on ptr arg - makes it equal 25 directly
int function2(int* arg) {
	*arg = 25; // reassign given pointer's value to 25 -> (*) is used to set value of provided address
}

// takes a function pointer and calls the function -> provided function must have same signature ( int func_name(int, int) )
void function3(int(*fn)(int, int)) {
	int foo1 = 50;
	int foo2 = 120;
	fn(foo1, foo2); // call provided callback function
} int callback(int arg1, int arg2) {
	return arg1 + arg2; // return added args
}