/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    NGL_Test.h                          :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGL_TEST_H
#define NGL_TEST_H

#include <string>
#include <functional>
#include <list>
#include <iostream>

class NGL_Test
{
public:
	NGL_Test(std::string name, std::function<void()> func)
	: _name(name), _func(func)
	{
		_tests.push_back(*this);
	}
	static void Run()
	{
		std::cout << "---------- Unit Testing ----------\n";
		for (auto e : _tests)
		{
			std::cout << "--- Starting tests for " << e._name << " ---\n";
			e._func();
		}
		std::cout << "----------------------------------\n";
	}

private:
	std::string					_name;
	std::function<void()>		_func;
	static std::list<NGL_Test>	_tests;
};

std::list<NGL_Test> NGL_Test::_tests;

#endif