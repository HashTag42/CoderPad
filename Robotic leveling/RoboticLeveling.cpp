#include <iostream>
#include <string>
#include <vector>
#include <numeric>  // for accumulate

using namespace std;

#define NDEBUG

#ifdef DEBUG
    #define DBG(x) std::cerr << "[DEBUG]" << x << std::endl
#else
    #define DBG(x)
#endif

class Solve
{
public:
    string solve(int clawPos, vector<int> boxes, bool boxInClaw) {
        string instruction = find_instruction(clawPos, boxes, boxInClaw);
        DBG("[solve][return] \"" + instruction + "\"");

        return instruction;
    }

    string find_instruction(int clawPos, vector<int> boxes, bool boxInClaw) {
        vector<int> delta_boxes = find_delta_boxes(boxes, boxInClaw);
        string instruction = "";

        if(delta_boxes[clawPos] < 0 && !boxInClaw)
            instruction = "PICK";
        else if(delta_boxes[clawPos] > 0 && boxInClaw)
            instruction = "PLACE";
        else    // We're on the move
            instruction = find_direction(clawPos, delta_boxes, boxInClaw);
        DBG("[find_instruction][return] \"" + instruction + "\"");

        return instruction;
    }

    vector<int> find_delta_boxes(vector<int> boxes, bool boxInClaw) {
        vector<int> target_boxes = find_target_boxes(boxes, boxInClaw);
        vector<int> delta_boxes(boxes.size(), 0);

        for(int i; i < boxes.size(); i++) {
            delta_boxes[i] = target_boxes[i] - boxes[i];
        }

        string msg = "[find_delta_boxes][return] {";
        for(int val: boxes)
            msg += val + ", ";
        msg += "}";
        DBG(msg);

        return delta_boxes;
    }

    vector<int> find_target_boxes(vector<int> boxes, bool boxInClaw) {
        int total_stacks = boxes.size();
        vector<int> target_boxes(total_stacks, 0);
        int total_boxes = accumulate(boxes.begin(), boxes.end(), 0);
        total_boxes += (boxInClaw) ? 1 : 0;
        int min_target = total_boxes / total_stacks;

        for(int i = 0; i < total_stacks; i++)
            target_boxes[i] = min_target;
        int remaining = total_boxes % total_stacks;
        if(remaining > 0)
            for(int i; i < remaining; i++)
                target_boxes[i] += 1;

        string msg = "[find_target_boxes][return] {";
        for(int val: boxes)
            msg += val + ", ";
        msg += "}";
        DBG(msg);

        return target_boxes;
    }

    string find_direction(int clawPos, vector<int> delta_boxes, bool boxInClaw) {
        string msg = "[find_direction][args](" + to_string(clawPos) + ", {";
        for(int val: delta_boxes)
            msg += to_string(val) + ", ";
        msg += "}, " + to_string(boxInClaw) += ")";
        DBG(msg);

        string direction = "";

        if(boxInClaw) {
            for(int i = 0; i < clawPos; i++) {
                if(delta_boxes[i] > 0) {
                    direction = "LEFT";
                    break;
                }
            }
            direction = (direction == "") ? "RIGHT" : "LEFT";
        }
        else {
            for(int j = 0; j < clawPos; j++) {
                if(delta_boxes[j] < 0) {
                    direction = "LEFT";
                    break;
                }
            }
            direction = (direction == "") ? "RIGHT" : "LEFT";
        }

        DBG("[find_direction][return] \"" + direction + "\"");

        return direction;
    }

};

string myAssert(string actual, string expected) {
    string msg = "[myAssert] ";

    if(actual == expected)
        msg += "PASS";
    else
        msg += "FAIL: \"" + actual + "\" != \"" + expected + "\"";

    return msg;
}

int main()
{
    Solve program = Solve();

    cout << myAssert(program.find_direction(0, {1, -1}, false), "RIGHT") << endl;
    cout << myAssert(program.find_direction(1, {-1, 1}, false), "LEFT") << endl;

    cout << myAssert(program.solve(0, {3, 1, 2, 2}, false), "PICK") << endl;
    cout << myAssert(program.solve(0, {2, 1, 2, 2}, true), "RIGHT") << endl;
    cout << myAssert(program.solve(1, {2, 1, 2, 2}, true), "PLACE") << endl;
    cout << myAssert(program.solve(0, {1, 0, 3, 0, 0, 1, 2}, false), "RIGHT") << endl;
    cout << myAssert(program.solve(0, {4, 2, 3, 4, 3, 2}, false), "PICK") << endl;
    cout << myAssert(program.solve(4, {0, 2, 1, 0, 0, 1}, false), "LEFT") << endl;
}
