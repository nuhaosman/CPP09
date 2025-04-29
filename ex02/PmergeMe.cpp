#include "PmergeMe.hpp"
#include <algorithm>


PmergeMe::PmergeMe(const std::vector<int> &input): sequence_(input), vectorTime_(0.0), listTime_(0.0)
{

}


PmergeMe::PmergeMe(const PmergeMe &other): sequence_(other.sequence_), vectorTime_(other.vectorTime_), listTime_(other.listTime_)
{

}


PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		sequence_ = other.sequence_;
		vectorTime_ = other.vectorTime_;
		listTime_ = other.listTime_;
	}
	return *this;
}


PmergeMe::~PmergeMe()
{

}


void PmergeMe::printSequence() const
{
	for (std::vector<int>::const_iterator it = sequence_.begin(); it != sequence_.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != sequence_.end())
		{
			std::cout << " ";
		}
	}
}


void PmergeMe::printTimings() const
{
	std::cout << "Time to process a range of " << sequence_.size() << " elements with std::vector : " << vectorTime_ << " us\n";
	std::cout << "Time to process a range of " << sequence_.size() << " elements with std::list : " << listTime_ << " us\n";
}
//us stands for microseconds, which is a unit of time equal to one millionth of a second (1 µs = 1/1,000,000 seconds)

void PmergeMe::sortWithVector()
{
	std::vector<int> vec = sequence_;
	clock_t start = clock();
	fordJohnsonVector(vec);
	clock_t end = clock();
	vectorTime_ = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}


void PmergeMe::sortWithList()
{
	std::list<int> lst(sequence_.begin(), sequence_.end());
	clock_t start = clock();
	fordJohnsonList(lst);
	clock_t end = clock();
	listTime_ = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	sequence_.assign(lst.begin(), lst.end());
}

//-----------------------------------------------------------------------------------------------

void PmergeMe::fordJohnsonVector(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return;

	std::vector<int> main;
	std::vector<int> pend;
	bool hasStraggler = (vec.size() % 2 != 0);
	int straggler = hasStraggler ? vec.back() : 0;

	for (size_t i = 0; i < vec.size() - (hasStraggler ? 1 : 0); i += 2)
	{
		int first = vec[i];
		int second = vec[i + 1];
		if (first > second)
		{
			main.push_back(second);
			pend.push_back(first);
		}
		else
		{
			main.push_back(first);
			pend.push_back(second);
		}
	}

	if (main.size() > 1)
		fordJohnsonVector(main);

	for (size_t i = 0; i < pend.size(); ++i)
	{
		binaryInsertVector(main, pend[i], main.size());
	}

	if (hasStraggler)
		binaryInsertVector(main, straggler, main.size());

	vec = main;
}

void PmergeMe::binaryInsertVector(std::vector<int> &main, int element, int end)
{
	int left = 0;
	int right = end;

	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (main[mid] < element)
			left = mid + 1;
		else
			right = mid;
	}

	main.insert(main.begin() + left, element);
}

//-----------------------------------------------------------------------------------------------

void PmergeMe::fordJohnsonList(std::list<int> &lst)
{
	if (lst.size() <= 1)
		return;

	std::list<int> main;
	std::list<int> pend;
	bool hasStraggler = (lst.size() % 2 != 0);
	int straggler = hasStraggler ? lst.back() : 0;
	std::list<int>::iterator it = lst.begin();

	while (it != lst.end())
	{
		int first = *it;
		++it;
		if (it == lst.end())
			break;
		int second = *it;
		++it;
		if (first > second)
		{
			main.push_back(second); //main small
			pend.push_back(first); // pend big
		}
		else
		{
			main.push_back(first);
			pend.push_back(second);
		}
	}

	if (main.size() > 1)
		fordJohnsonList(main);

	for (std::list<int>::iterator pendIt = pend.begin(); pendIt != pend.end(); ++pendIt)
	{
		binaryInsertList(main, *pendIt);
	}

	if (hasStraggler)
		binaryInsertList(main, straggler);

	lst = main;
}


void PmergeMe::binaryInsertList(std::list<int> &main, int element)
{
	std::list<int>::iterator it = main.begin();
	while (it != main.end() && *it < element)
	{
		++it;
	}
	main.insert(it, element);
}

//fordJohnsonList:
// The algorithm works by dividing the list into pairs, sorting those pairs,
// and then recursively sorting the main list while inserting the "pend" elements
// (the second elements of the pairs) back into the sorted list using binary insertion.
// If there is an odd element (straggler), it is handled separately at the end.