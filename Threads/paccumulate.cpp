#include <thread>
#include <iostream>
#include <numeric>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

template<typename Iterator, typename T>
struct accumulateBlock
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result);
	}
};


template<typename Iterator, typename T>
T parallelAccumulate(Iterator first, Iterator last, T init)
{
	//std::distance returns numbers of hops from first to last iterator
	unsigned long const length = std::distance(first, last);
	if (!length)
	{
		return init;
	}

	unsigned long const minPerThread = 25;
	unsigned long const maxThread = (length + minPerThread - 1) / minPerThread;
	unsigned long const hardwareThreads = std::thread::hardware_concurrency();

	unsigned long const numThreads = std::min((hardwareThreads != 0 ? hardwareThreads : 2), maxThread);
	//number of threads to run is the minimum between the calculated maximum 
	//number of threads and the number of threads that the hardware can support

	//number of entries to compute for each thread
	unsigned long const blockSize = length / numThreads;

	std::vector<T> results(numThreads);//intermediate results of each thread
	//because threads cannot return values directly we must pass some kind of reference to the thread in order to get output
		//there are also futures which we will see later

	std::vector<std::thread> threads(numThreads - 1); //-1 because we already have the main thread

	//block is our data that we want to accumulate 
	//we have already determined the block size for each of our threads
	//so we make two iterators into our data start and end and send that part of our data to the thread we are creating

	Iterator blockStart = first;
	for (unsigned long threadId = 0; threadId < (numThreads - 1); threadId++)
	{
		Iterator blockEnd = blockStart;
		std::advance(blockEnd, blockSize);
		std::cout << "creating thread with id : " << threadId << "\n";
		threads[threadId] = std::thread(
			accumulateBlock<Iterator, T>(),
			blockStart, blockEnd, std::ref(results[threadId])
		);
		blockStart = blockEnd;
	}

	//we need this because this is the work to be done by our main thread 
	//the main thread takes care of the last block
	accumulateBlock<Iterator, T>()(
		blockStart, last, results[numThreads - 1]);


	//std::mem_fn returns callable function pointer to member function
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));


	//we need to accumulate the intermediate result list
	std::accumulate(results.begin(), results.end(), init);

}


int main() {
	std::vector<int> data{ 1,23,4,1,25,5,12,51,23,1,24,125,251,25,12512,5,125,234,234,23,4,32,42,56,234,23,4,234,32,4,23,423,4,234,23,4,234,23,432,42,3,5,5,23,4,23,4,23,6,64,6547,547,568,768,7,68,76 };

	parallelAccumulate(data.begin(), data.end(), data);

	//for (auto value : result) {
	//	std::cout << "result : " << value << "\n";
	//}
	//right result is a vector of vectors then 
	//std::cout << "result from parallel accumulation : " << result << "\n";

	return 0;
}