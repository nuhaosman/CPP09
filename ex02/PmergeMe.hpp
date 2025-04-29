#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <ctime>

class PmergeMe
{
	public:
		PmergeMe(const std::vector<int> &input);
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void sortWithVector();
		void sortWithList();
		void printSequence() const;
		void printTimings() const;

	private:
		std::vector<int> sequence_;
		double vectorTime_;        
		double listTime_;          

		void fordJohnsonVector(std::vector<int> &vec);
		void fordJohnsonList(std::list<int> &lst);
		void binaryInsertVector(std::vector<int> &main, int element, int end);
		void binaryInsertList(std::list<int> &main, int element);
};
#endif