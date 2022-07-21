#include <iostream>
#include <chrono>


//day night system 




void fu() {
	auto i = 10;
	while (i > 0) {
		i -= 1;
	}
}



int main() {
	std::chrono::seconds interval{ 10 };
	//seconds s = 3 not implicitly constructible from int
	//std::cout << interval << '\n'; printing seconds is not that easy
	//we need to use .count() to get the long long out of seconds
	std::cout << "timer interval set : " << interval.count() << "\n";

	interval += std::chrono::seconds{1};
	interval -= std::chrono::seconds{1}; 
	interval += std::chrono::minutes{ 1 };

	//i cannot add milliseconds to seconds but i can add minutes to seconds 
	//and i can add seconds to milliseconds

	//if i wanted to add milliseconds to seconds i would need the duration_cast
	interval -= std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds{ 100 });

	//we can add or subtract durations
	//we can also do comparisions between duration types 
	
	//ranges 
	auto minSeconds = std::chrono::seconds::min();
	auto maxSeconds = std::chrono::seconds::max();
	std::cout << "min number of seconds for the chrono type : " << minSeconds.count() << "\n";
	std::cout << "max number of seconds for the chrono type : " << maxSeconds.count() << "\n";
	//surprise the ranges are just line signed long long but really

	//milliseconds type
	//works the same as seconds type and has the same range 
	std::chrono::milliseconds millisecondInterval{ 100 };
	//as well as microseconds 
	std::chrono::microseconds microsecondInterval{ 100 };

	//it is important that ints do no implicitly convert to seconds or milliseconds etc
	//because they are ambiguous also if they were to convert 
	//function like addtime(3) we would not know if 3 becomes implicitly converted into 
	//a second or a millisecond in the function
	//it creates unpredictable behavior from the function call		

	//however std::chrono::seconds can be compared with std::chrono::milliseconds 
	//3 seconds will convert to 3000 milliseconds 

	std::chrono::seconds interval2{2};

	//we can also compare seconds and milliseconds 
	auto result = interval2 < millisecondInterval;
	auto result2 = interval2 < microsecondInterval;
	auto result3 = millisecondInterval < interval2;
	auto result4 = microsecondInterval < interval2;



	//loss less convertions 
	//seconds -> milliseconds
	millisecondInterval = interval2; 
	millisecondInterval += std::chrono::seconds{ 1 };
	//this works because its a loss less convertion
	//pretty much going from higher order of magnitude unit to a lower one is loss less
	//ms -> micro seconds -> ms seconds -> micro etc


	//lossy convertions 
	//for implicit convertions these are not allowed
	//milliseconds -> seconds or going from a lower order of magnitude unit to a higher
	
	//interval = millisecondInterval; error : no convertion this does not compile

	//but there are cases we might want to do this 
	//we have to be explicit !

	interval = std::chrono::duration_cast<std::chrono::seconds>(millisecondInterval);
	
	//and use this duration_cast function
	//and it will truncate towards zero 
	//so im guessing 700 ms will equal 0 seconds ?
	auto testTruncation = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds{700});
	
	std::cout << "TEST TRUNCAITON : " << std::chrono::milliseconds{ 700 }.count() << " ms\n";
	std::cout << "TEST TRUNCAITON : " << testTruncation.count() << " s\n";
	//indeed 700ms gets trucated to 0
	//truncation towards 0 for negative durations actually truncates up 
	//-700 will truncate up to 0

	//there are ways to change the rounding behavior such as 
	//std::chrono::floor<seconds>()
	//std::chrono::round<>;
    //std::chrono::seil<>;
	//only use the explicit duration_cast<> when necessary

	//should be able to define what representation we want for our duration 
	//instead of a 64 bit long long we could want 32 bit etc 
	using seconds32 = std::chrono::duration<uint16_t>;
	//not that we need the keyword using 


	using frames = std::chrono::duration<int32_t, std::ratio<1, 60>>;
	//here we have a duration of 1/60
	std::chrono::duration<float, std::milli> d = frames{ 10 };
	std::cout << "time for 10 frames : " << d.count() << "\n";


	//every chrono type like 
		// std::chrono::seconds
		// std::chrono::milliseconds
		// std::chrono::minutes

	//is equivalent to a [reprensentation | ratio]
	//where the representation is the type in memory like int16 etc
	//and the ratio defines what a unit represents
	//
	//std::chrono::milliseconds == std::chrono::duration<int64_t, 1/1000>
	//std::chrono::seconds == std::chrono::duration<int64_t, 1/1> 
	//so those types are just defined using this std::chrono::duration

	//and we can define our own
	//using frames = std::chrono::duration<int32_t, std::ratio<1, 60>>;


	//good quote from lecture
	//seconds is to std::chrono::duration<int64_t, std::ratio<1,1>>
	//as
	//string is to basic_string<char, char_traits<char>, allocator<char>>

	//std::chrono::duration is a powerfull template type and we make specializations of it
	//just like std::string is

	//durations means a time span situated nowhere specifically in time IRL 
	//time_points mean a specific point in time IRL with respect to some clock 
	
	//time points and durations can have the same representaion but mean completely different things.

	//time points can be subtracted and you will get a duration but two time points cannot be added
	//you can add and subtract a duration from a time_point


	//clocks are a bundle of a time point a duration and a function to get the current time 
	std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::now();
	std::cout << "The time now : " << timepoint.time_since_epoch().count() << "\n";
	std::cout << "The time now in seconds : " << std::chrono::time_point_cast<std::chrono::seconds>(timepoint).time_since_epoch().count() << "\n";
	std::cout << "The time now in days : " << std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<86400>>>(timepoint).time_since_epoch().count() << "\n";

	std::chrono::steady_clock::time_point steady = std::chrono::steady_clock::now();
	std::cout << "stopwatch : " << steady.time_since_epoch().count() << "\n";

	//every time_point is associated with a clock 
	//time_points associated with different clocks do not convert to one another
	//Applications can have as many clocks as they want to
	// two supplied :
	//	std::chrono::steady_clock
	//	std::chrono::system_clock
	//  ignore std::chrono::high_resolution_clock it is an alias for the above
	// 
	// 
	//std::chrono::steady_clock timepoint2 = timepoint;

	//system_clock can tell you what time of the day it is and what day only system_clock has a relationship to any calendar at all

	//steady_clock is just like a stopwatch its great at timing things but there is no way to get the time of the day from a stopwatch

	//whatever clock we chose we get its nested time point like so 
	//clock::time_point tp = clock::now()


	//example 
	//timing a function
	auto t0 = std::chrono::steady_clock::now();
	fu();
	auto t1 = std::chrono::steady_clock::now();

	std::cout << "time for function : " << std::chrono::duration<double>{t1 - t0}.count() << " s\n";
	std::cout << "time for function : " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms\n";



	auto timeIntervalPrint = std::chrono::seconds{ 5 };
	while (true) {
		auto initialTimeReading = std::chrono::steady_clock::now();
		auto t0 = initialTimeReading;
		while (t0 < initialTimeReading + timeIntervalPrint) {
			t0 = std::chrono::steady_clock::now();
		}
		std::cout << "5 seconds passed :)\n";
		
	}


	//the de facto standard for system_clock is that it is counting seconds since 1970-01-01 UTC 
	//




	return 0;
}


void printEvery5Seconds() {
	auto timeIntervalPrint = std::chrono::seconds{ 5 };
	while (true) {
		auto initialTimeReading = std::chrono::steady_clock::now();
		auto t0 = initialTimeReading;
		while (t0 < initialTimeReading + timeIntervalPrint) {
			t0 = std::chrono::steady_clock::now();
		}
		std::cout << "5 seconds passed :)\n";

	}
}



auto addTime(std::chrono::seconds x, std::chrono::seconds y) {
	return x + y;
}