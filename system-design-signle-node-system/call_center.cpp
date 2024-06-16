/*
https://github.com/donnemartin/system-design-primer/blob/master/solutions/object_oriented_design/call_center/call_center.ipynb

Constraints and assumptions

What levels of employees are in the call center?
Operator, supervisor, director
Can we assume operators always get the initial calls?
Yes
If there is no available operators or the operator can't handle the call, does the call go to the supervisors?
Yes
If there is no available supervisors or the supervisor can't handle the call, does the call go to the directors?
Yes
Can we assume the directors can handle all calls?
Yes
What happens if nobody can answer the call?
It gets queued
Do we need to handle 'VIP' calls where we put someone to the front of the line?
No
Can we assume inputs are valid or do we have to validate them?
Assume they're valid

*/
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

enum class Rank {
    OPERATOR = 0,
    SUPERVISOR = 1,
    DIRECTOR = 2
};

class CallState {
public:
    static const int READY = 0;
    static const int IN_PROGRESS = 1;
    static const int COMPLETE = 2;
};

class Call {
public:
    Call(Rank rank) : state(CallState::READY), rank(rank), employee(nullptr) {}
    int state;
    Rank rank;
    class Employee* employee;
};

class Employee {
public:
    Employee(int employee_id, std::string name, Rank rank, class CallCenter* call_center)
        : employee_id(employee_id), name(name), rank(rank), call(nullptr), call_center(call_center) {}

    virtual void escalate_call() = 0;

protected:
    int employee_id;
    std::string name;
    Rank rank;
    Call* call;
    CallCenter* call_center;

    void _escalate_call() {
        call->state = CallState::READY;
        Call* escalated_call = call;
        call = nullptr;
        call_center->notify_call_escalated(escalated_call);
    }

public:
    void take_call(Call* call) {
        this->call = call;
        call->employee = this;
        call->state = CallState::IN_PROGRESS;
    }

    void complete_call() {
        call->state = CallState::COMPLETE;
        call_center->notify_call_completed(call);
    }
};

class Operator : public Employee {
public:
    Operator(int employee_id, std::string name, CallCenter* call_center)
        : Employee(employee_id, name, Rank::OPERATOR, call_center) {}

    void escalate_call() override {
        call->rank = Rank::SUPERVISOR;
        _escalate_call();
    }
};

class Supervisor : public Employee {
public:
    Supervisor(int employee_id, std::string name, CallCenter* call_center)
        : Employee(employee_id, name, Rank::SUPERVISOR, call_center) {}

    void escalate_call() override {
        call->rank = Rank::DIRECTOR;
        _escalate_call();
    }
};

class Director : public Employee {
public:
    Director(int employee_id, std::string name, CallCenter* call_center)
        : Employee(employee_id, name, Rank::DIRECTOR, call_center) {}

    void escalate_call() override {
        throw std::runtime_error("Directors must be able to handle any call");
    }
};

class CallCenter {
public:
    CallCenter(std::vector<Operator>& operators, std::vector<Supervisor>& supervisors, std::vector<Director>& directors)
        : operators(operators), supervisors(supervisors), directors(directors) {}

    void dispatch_call(Call* call) {
        if (call->rank != Rank::OPERATOR && call->rank != Rank::SUPERVISOR && call->rank != Rank::DIRECTOR) {
            throw std::invalid_argument("Invalid call rank: " + std::to_string(static_cast<int>(call->rank)));
        }

        Employee* employee = nullptr;
        if (call->rank == Rank::OPERATOR) {
            employee = _dispatch_call(call, operators);
        }
        if (call->rank == Rank::SUPERVISOR || employee == nullptr) {
            employee = _dispatch_call(call, supervisors);
        }
        if (call->rank == Rank::DIRECTOR || employee == nullptr) {
            employee = _dispatch_call(call, directors);
        }

        if (employee == nullptr) {
            queued_calls.push(call);
        }
    }

    void notify_call_escalated(Call* call) {
        // Implement this method
    }

    void notify_call_completed(Call* call) {
        // Implement this method
    }

    void dispatch_queued_call_to_newly_freed_employee(Call* call, Employee* employee) {
        // Implement this method
    }

private:
    std::vector<Operator> operators;
    std::vector<Supervisor> supervisors;
    std::vector<Director> directors;
    std::queue<Call*> queued_calls;

    Employee* _dispatch_call(Call* call, std::vector<Employee*>& employees) {
        for (auto employee : employees) {
            if (employee->call == nullptr) {
                employee->take_call(call);
                return employee;
            }
        }
        return nullptr;
    }
};

