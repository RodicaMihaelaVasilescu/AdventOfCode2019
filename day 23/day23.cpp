#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct packet
{
    vector<long long> instructions;
    int instructionIndex = 0;
    int relativeBase = 0;
    queue<long long> input;
    queue<long long> output;
};

bool runInstructions(int& i, vector<long long>& instructions, int& relativeBase,
    queue<long long>& input, queue<long long>& output)
{
    while (true)
    {
        long long opcode = instructions[i] % 100;

        long long firstParameterMode = instructions[i] / 100 % 10;
        long long secondParameterMode = instructions[i] / 1000 % 10;
        long long thirdParameterMode = instructions[i] / 10000;

        long long A = firstParameterMode == 1 ? i + 1 : firstParameterMode == 0 ? instructions[i + 1] : instructions[i + 1] + relativeBase;
        long long B = secondParameterMode == 1 ? i + 2 : secondParameterMode == 0 ? instructions[i + 2] : instructions[i + 2] + relativeBase;
        long long C = thirdParameterMode == 1 ? i + 3 : thirdParameterMode == 0 ? instructions[i + 3] : instructions[i + 3] + relativeBase;

        if (opcode == 1)
        {
            instructions[C] = instructions[A] + instructions[B];
            i += 4;
        }
        else if (opcode == 2)
        {
            instructions[C] = instructions[A] * instructions[B];
            i += 4;
        }
        else if (opcode == 3)
        {
            if (!input.empty())
            {
                instructions[A] = input.front();
                input.pop();
            }
            else
            {
                return false;
            }
            i += 2;
        }
        else if (opcode == 4)
        {
            output.push(instructions[A]);
            i += 2;
        }
        else if (opcode == 5)
        {
            if (instructions[A] != 0)
            {
                i = instructions[B];
                continue;
            }

            i += 3;
        }
        else if (opcode == 6)
        {
            if (instructions[A] == 0)
            {
                i = instructions[B];
                continue;
            }

            i += 3;
        }
        else if (opcode == 7)
        {
            if (instructions[A] < instructions[B])
            {
                instructions[C] = 1;
            }
            else
            {
                instructions[C] = 0;
            }
            i += 4;
        }
        else if (opcode == 8)
        {
            if (instructions[A] == instructions[B])
            {
                instructions[C] = 1;
            }
            else
            {
                instructions[C] = 0;
            }
            i += 4;
        }
        else if (opcode == 9)
        {
            relativeBase += instructions[A];
            i += 2;
        }
        else if (opcode == 99)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void SolvePart1AndPart2(vector<long long> instructions)
{
    int solutionPart1 = 0;
    pair<long long, long long> lastPacket, secondToLastPacket;

    vector<packet> packets(50);
    for (auto& packet : packets)
    {
        static int index = 0;
        packet.input.push(index++);
        packet.input.push(-1); // "if no packet is waiting, input instructions should receive -1"
        packet.instructions = instructions;
        runInstructions(packet.instructionIndex, packet.instructions, packet.relativeBase, packet.input, packet.output);
    }

    while (true)
    {
        for (auto& packet : packets)
        {
            runInstructions(packet.instructionIndex, packet.instructions, packet.relativeBase, packet.input, packet.output);
            while (!packet.output.empty())
            {
                /*
                    "To send a packet to another computer, the NIC will use three output instructions
                    that provide the destination address of the packet followed by its X and Y values"
                */
                long long networkAddress = packet.output.front();
                packet.output.pop();
                lastPacket.first = packet.output.front();
                packet.output.pop();
                lastPacket.second = packet.output.front();
                packet.output.pop();

                if (networkAddress == 255)
                {
                    if (solutionPart1 == 0)
                    {
                        // the Y value of the first packet sent to address 255
                        solutionPart1 = lastPacket.second;
                    }
                }
                else
                {
                    packets[networkAddress].input.push(lastPacket.first);
                    packets[networkAddress].input.push(lastPacket.second);
                }
            }
        }

        /*
             "If all computers have empty incoming packet queues and are continuously trying
             to receive packets without sending packets, the network is considered idle."
        */
        auto packetWithInput = find_if_not(packets.begin(), packets.end(), [](auto packet)
            {
                return packet.input.empty();
            });

        if (packetWithInput == packets.end()) // network is idle
        {
            // "Once the network is idle, the NAT sends only the last packet it received to address 0"
            packets[0].input.push(lastPacket.first);
            packets[0].input.push(lastPacket.second);

            if (lastPacket == secondToLastPacket)
            {
                cout << "Part 1: " << solutionPart1 << endl;
                cout << "Part 2: " << lastPacket.second << endl;
                return;
            }
            secondToLastPacket = lastPacket; // the antepenultimate packet
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<long long> instructions;
    long long number;
    char delimiter;

    while (cin >> number)
    {
        cin >> delimiter; // ',' character
        instructions.push_back(number);
    }

    instructions.resize(10000, 0);

    SolvePart1AndPart2(instructions);

    return 0;
}