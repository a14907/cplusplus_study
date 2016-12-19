#pragma once

#ifndef TEST_H

#define TEST_H

class person
{
public:
	person();
	~person();
	char name[4];
	int age;
    void set_score(int n);

private:
	int score;
};


#endif // !TEST_H
