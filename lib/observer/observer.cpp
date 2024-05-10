
#include "observer.h"

#ifdef OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION
Observer::~Observer()
{
    // Before deleting, remove itself from all subjects that it observes
    for (uint32_t i = 0; i < numberOfSubjects; i++)
    {
        subjects[i]->removeObserver(this);
    }
}

// Called only in subject->addObserver() function
bool Observer::addSubject(Subject* subject)
{
    // Check whether the subject is already in the array
    for (uint32_t i = 0; i < numberOfSubjects; i++)
    {
        if (subjects[i] == subject)
        {
            return false;
        }
    }

    // If it is not in the array, add to the end
    if (numberOfSubjects < MAX_SUBJECT_NUMBER)
    {
        subjects[numberOfSubjects++] = subject;
        return true;
    }
    return false;
}

// Called only when the subject is deleted, and the subject removes the observer
bool Observer::removeSubject(Subject* subject)
{
    // Linear sarch on the array
    for (uint32_t i = 0; i < numberOfSubjects; i++)
    {
        if (subjects[i] == subject)
        {
            subjects[i] = subjects[--numberOfSubjects];
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------------------------// 


void Subject::notify(const Verlet& verlet, enum Event event) const
{
    for (uint32_t i = 0; i < numberOfObservers; i++)
    {
        observers[i]->onNotify(verlet, event);
    }
}

Subject::~Subject()
{
    // Before deleting, remove itself from all observers that it notifies
    for (uint32_t i = 0; i < numberOfObservers; i++)
    {
        observers[i]->removeSubject(this);
    }
}

void Subject::addObserver(Observer* observer)
{
    // Check whether the observer is already in the array
    for (uint32_t i = 0; i < numberOfObservers; i++)
    {
        if (observers[i] == observer)
        {
            return;
        }
    }

    // If it is not in the array, add to the end
    if (numberOfObservers < MAX_OBSERVER_NUMBER && observer->addSubject(this))
    {
        observers[numberOfObservers++] = observer;
    }
}

void Subject::removeObserver(Observer* observer)
{
    // Linear sarch on the array
    for (uint32_t i = 0; i < numberOfObservers; i++)
    {
        if (observers[i] == observer)
        {
            if (observer->removeSubject(this))
            {
                observers[i] = observers[--numberOfObservers];
            }
            return;
        }
    }
}

#else

Observer::~Observer()
{
    if (next != nullptr)
    {
        next->prev = prev;
    }
    if (prev != nullptr)
    {
        prev->next = next;
    }
}

// -----------------------------------------------------------------------------// 

Subject::~Subject()
{
    Observer* observer = head;
    while (observer != nullptr)
    {
        head = observer->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        observer->next = nullptr;
        observer = head;
    }
}

void Subject::notify(const Verlet& verlet, enum Event event) const
{
    Observer* observer = head;
    while (observer != nullptr)
    {
        observer->onNotify(verlet, event);
        observer = observer->next;
    }
}

void Subject::addObserver(Observer* observer)
{
    // Linear search over the linked list
    Observer* current = head;
    while (current != nullptr)
    {
        if (current == observer) { return; }
        current = current->next;
    }

    // If the observer is not in the list, add it to the beginning
    observer->next = head;
    if (observer->next != nullptr)
    {
        observer->next->prev = observer;
    }
    head = observer;
}

void Subject::removeObserver(Observer* observer)
{
    // Check if the observer is the head of the list
    if (head == observer)
    {
        head = observer->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        observer->next = nullptr;
        return;
    }

    // Find the observer in the list and remove it
    Observer* current = head;
    while (current != nullptr)
    {
        if (current->next == observer)
        {
            current->next = observer->next;
            observer->prev = nullptr;
            if (observer->next != nullptr)
            {
                observer->next->prev = current;
            }
            observer->next = nullptr;
            return;
        }
        current = current->next;
    }
}

#endif // OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

