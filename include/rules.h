//
//  rules.h
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#ifndef rules_h
#define rules_h

class IRule {
public:
    virtual bool applyRule(int, bool) = 0;
    virtual ~IRule(){}
};

class r3_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r3_3(){}
};

class r13_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r13_3(){}
};

class r23_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r23_3(){}
};

class r34_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r34_3(){}
};

class r35_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r35_3(){}
};

class r2_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r2_3(){}
};

class r24_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r24_3(){}
};

class r245_3 : public IRule {
public:
    bool applyRule(int, bool);
    ~r245_3(){}
};

class r125_36 : public IRule {
public:
    bool applyRule(int, bool);
    ~r125_36(){}
};
#endif /* rules_h */
