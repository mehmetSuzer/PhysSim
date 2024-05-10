
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "verlet.h"

enum Event {
    EVENT0 = 0,
    EVENT1,
    EVENT2,
    EVENT3,
    EVENT4,
    EVENT5,
    SUBJECT_DEAD,
};

#define OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

#ifdef OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION
#define MAX_SUBJECT_NUMBER  20UL
#define MAX_OBSERVER_NUMBER 20UL

class Subject;

class Observer
{
    friend class Subject;

private:
    Subject* subjects[MAX_SUBJECT_NUMBER];
    uint32_t numberOfSubjects = 0;

    bool addSubject(Subject* subject);
    bool removeSubject(Subject* subject);

public:
    ~Observer();
    virtual void onNotify(const Verlet& verlet, enum Event event) = 0;
};

class Subject
{
private:
    Observer* observers[MAX_OBSERVER_NUMBER];
    uint8_t numberOfObservers = 0;

protected:
    void notify(const Verlet& verlet, enum Event event) const;

public:
    ~Subject();

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};

#else
class Observer
{
    friend class Subject;

public:
    ~Observer();
    virtual void onNotify(const Verlet& verlet, enum Event event) = 0;

protected:
    Observer() : prev(nullptr), next(nullptr) {}

private:
    Observer* prev;
    Observer* next;
};

class Subject
{
private:
    Observer* head;

protected:
    Subject() : head(nullptr) {}

    void notify(const Verlet& verlet, enum Event event) const;

public:
    ~Subject();

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};

#endif // OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

#endif // __OBSERVER_H__
