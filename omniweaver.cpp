#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <limits>
#include <stdexcept>

// ================================================
// OMNIWEAVER
// Universal AI Integration & Orchestration Engine
// ================================================

namespace OmniCore
{
    const std::string VERSION = "1.0.0";

    const std::string DIRECTIVE =
        "Connect, coordinate, integrate, and expand "
        "without compromising system integrity.";
}

// ================================================
// TIME UTILITY
// ================================================

std::string CurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm local{};

#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif

    std::ostringstream output;

    output << std::put_time(
        &local, "%Y-%m-%d %H:%M:%S"
    );

    return output.str();
}

// ================================================
// MESSAGE STRUCTURE
// ================================================

struct WeaverMessage
{
    std::string sender;
    std::string recipient;
    std::string payload;
    std::string timestamp;
};

// ================================================
// ACTIVITY LOGGER
// ================================================

class WeaverLogger
{
private:
    std::string filename = "omniweaver_log.txt";

public:
    void Record(const std::string& event)
    {
        std::ofstream file(filename, std::ios::app);

        if (file)
        {
            file << "[" << CurrentTime() << "] "
                 << event << "\n";
        }
    }

    void Display()
    {
        std::ifstream file(filename);

        if (!file)
        {
            std::cout << "\nNo activity recorded.\n";
            return;
        }

        std::string line;

        std::cout << "\n========== ACTIVITY LOG ==========\n";

        while (std::getline(file, line))
        {
            std::cout << line << "\n";
        }
    }
};

// ================================================
// SUBSYSTEM INTERFACE
// ================================================

class IWeaverSubsystem
{
public:
    virtual ~IWeaverSubsystem() = default;

    virtual std::string Name() const = 0;

    virtual std::string Description() const = 0;

    virtual std::string Process(
        const std::string& input
    ) = 0;

    virtual bool IsOperational() const
    {
        return true;
    }
};

// ================================================
// MATHEMATICAL SUBSYSTEM
// ================================================

class WeaverMath : public IWeaverSubsystem
{
public:

    std::string Name() const override
    {
        return "MathEngine";
    }

    std::string Description() const override
    {
        return "Mathematical computation and evaluation.";
    }

    std::string Process(
        const std::string& input
    ) override
    {
        std::istringstream stream(input);

        std::string operation;
        double a, b;

        stream >> operation;

        if (operation != "add" &&
            operation != "subtract" &&
            operation != "multiply" &&
            operation != "divide")
        {
            return "MathEngine: Unknown operation. "
                   "Use add, subtract, multiply, or divide.";
        }

        if (!(stream >> a >> b))
        {
            return "MathEngine: Invalid input. "
                   "Example: multiply 5 10";
        }

        double result = 0.0;

        if (operation == "add")
        {
            result = a + b;
        }
        else if (operation == "subtract")
        {
            result = a - b;
        }
        else if (operation == "multiply")
        {
            result = a * b;
        }
        else if (operation == "divide")
        {
            if (b == 0.0)
                return "MathEngine: Division by zero rejected.";

            result = a / b;
        }

        std::ostringstream output;

        output << std::setprecision(12)
               << "Calculation: " << a << " "
               << operation << " " << b
               << " = " << result;

        return output.str();
    }
};

// ================================================
// PERSISTENT MEMORY SUBSYSTEM
// ================================================

class WeaverMemory : public IWeaverSubsystem
{
private:
    std::string filename = "omniweaver_memory.txt";

public:

    std::string Name() const override
    {
        return "MemoryEngine";
    }

    std::string Description() const override
    {
        return "Persistent local memory storage and retrieval.";
    }

    std::string Process(
        const std::string& input
    ) override
    {
        if (input.rfind("remember ", 0) == 0)
        {
            std::string information =
                input.substr(9);

            if (information.empty())
                return "MemoryEngine: Nothing to save.";

            std::ofstream file(
                filename,
                std::ios::app
            );

            if (!file)
                return "MemoryEngine: Storage unavailable.";

            file << "[" << CurrentTime() << "] "
                 << information << "\n";

            return "MemoryEngine: Information stored successfully.";
        }

        if (input == "recall")
        {
            std::ifstream file(filename);

            if (!file)
                return "MemoryEngine: No stored memories found.";

            std::ostringstream output;
            std::string line;

            output << "\nStored memories:\n";

            while (std::getline(file, line))
            {
                output << line << "\n";
            }

            return output.str();
        }

        return "MemoryEngine: Commands are remember and recall.";
    }
};

// ================================================
// OBSERVER SUBSYSTEM
// ================================================

class WeaverObserver : public IWeaverSubsystem
{
public:

    std::string Name() const override
    {
        return "ObserverEngine";
    }

    std::string Description() const override
    {
        return "Input observation and structured examination.";
    }

    std::string Process(
        const std::string& input
    ) override
    {
        if (input.empty())
            return "ObserverEngine: No input received.";

        std::ostringstream output;

        output << "ObserverEngine Report\n";
        output << "---------------------\n";

        output << "Input length: "
               << input.length() << " characters\n";

        output << "Word count: ";

        std::istringstream words(input);
        std::string word;
        int count = 0;

        while (words >> word)
            ++count;

        output << count << "\n";

        output << "Observation: Input received and "
                  "ready for further processing.";

        return output.str();
    }
};

// ================================================
// ARCHIVE SUBSYSTEM
// ================================================

class WeaverArchive : public IWeaverSubsystem
{
private:
    std::string filename = "omniweaver_archive.txt";

public:

    std::string Name() const override
    {
        return "ArchiveEngine";
    }

    std::string Description() const override
    {
        return "Local message and event archiving.";
    }

    std::string Process(
        const std::string& input
    ) override
    {
        std::ofstream file(filename, std::ios::app);

        if (!file)
            return "ArchiveEngine: Unable to access archive.";

        file << "[" << CurrentTime() << "] "
             << input << "\n";

        return "ArchiveEngine: Event archived.";
    }
};

// ================================================
// OMNIWEAVER CORE
// ================================================

class OmniWeaver
{
private:

    std::unordered_map<
        std::string,
        std::unique_ptr<IWeaverSubsystem>
    > subsystems;

    std::vector<WeaverMessage> messageHistory;

    WeaverLogger logger;

    bool running = false;

    int totalMessages = 0;

    // --------------------------------------------
    // REGISTER SUBSYSTEM
    // --------------------------------------------

    void Register(
        std::unique_ptr<IWeaverSubsystem> subsystem
    )
    {
        std::string name = subsystem->Name();

        if (subsystems.find(name) != subsystems.end())
            return;

        logger.Record("Registered subsystem: " + name);

        subsystems.emplace(
            name,
            std::move(subsystem)
        );
    }

    // --------------------------------------------
    // ROUTE MESSAGE
    // --------------------------------------------

    std::string Route(
        const std::string& destination,
        const std::string& payload
    )
    {
        auto found = subsystems.find(destination);

        if (found == subsystems.end())
        {
            return "OmniWeaver: Subsystem not found: "
                   + destination;
        }

        if (!found->second->IsOperational())
        {
            return "OmniWeaver: Subsystem unavailable.";
        }

        WeaverMessage message;

        message.sender = "OmniWeaver";
        message.recipient = destination;
        message.payload = payload;
        message.timestamp = CurrentTime();

        messageHistory.push_back(message);
        ++totalMessages;

        logger.Record(
            "Message routed to " + destination
        );

        return found->second->Process(payload);
    }

    // --------------------------------------------
    // BROADCAST MESSAGE
    // --------------------------------------------

    void Broadcast(const std::string& payload)
    {
        std::cout << "\n========== BROADCAST ==========\n";

        for (auto& item : subsystems)
        {
            std::cout << "\n[" << item.first << "]\n";

            std::cout << item.second->Process(payload)
                      << "\n";

            ++totalMessages;
        }

        logger.Record("Broadcast completed.");
    }

    // --------------------------------------------
    // SYSTEM DISCOVERY
    // --------------------------------------------

    void DiscoverSystems()
    {
        std::cout << "\n========== REGISTERED SYSTEMS ==========\n";

        for (const auto& item : subsystems)
        {
            std::cout << "\nSystem: "
                      << item.second->Name();

            std::cout << "\nDescription: "
                      << item.second->Description();

            std::cout << "\nStatus: "
                      << (item.second->IsOperational()
                          ? "OPERATIONAL"
                          : "OFFLINE");

            std::cout << "\n";
        }
    }

    // --------------------------------------------
    // SYSTEM STATUS
    // --------------------------------------------

    void Status()
    {
        std::cout << "\n========== OMNIWEAVER STATUS ==========\n";

        std::cout << "Version: "
                  << OmniCore::VERSION << "\n";

        std::cout << "Core: ONLINE\n";

        std::cout << "Registered systems: "
                  << subsystems.size() << "\n";

        std::cout << "Messages processed: "
                  << totalMessages << "\n";

        std::cout << "Stored session messages: "
                  << messageHistory.size() << "\n";

        std::cout << "Timestamp: "
                  << CurrentTime() << "\n";

        DiscoverSystems();
    }

    // --------------------------------------------
    // WORKFLOW ORCHESTRATION
    // --------------------------------------------

    void ExecuteWorkflow(const std::string& input)
    {
        std::cout << "\n========== WEAVER WORKFLOW ==========\n";

        std::cout << "\nStep 1: Observer examination\n";

        std::cout << Route(
            "ObserverEngine",
            input
        ) << "\n";

        std::cout << "\nStep 2: Archive event\n";

        std::cout << Route(
            "ArchiveEngine",
            "Workflow input: " + input
        ) << "\n";

        std::cout << "\nStep 3: Memory storage\n";

        std::cout << Route(
            "MemoryEngine",
            "remember Workflow input: " + input
        ) << "\n";

        std::cout << "\nWorkflow completed.\n";

        logger.Record("Multi-system workflow completed.");
    }

    // --------------------------------------------
    // HELP
    // --------------------------------------------

    void Help()
    {
        std::cout << "\n========== OMNIWEAVER COMMANDS ==========\n";

        std::cout << "help\n";
        std::cout << "systems\n";
        std::cout << "status\n";
        std::cout << "send <system> <message>\n";
        std::cout << "broadcast <message>\n";
        std::cout << "weave <message>\n";
        std::cout << "calc <operation> <number> <number>\n";
        std::cout << "remember <information>\n";
        std::cout << "recall\n";
        std::cout << "log\n";
        std::cout << "quit\n";

        std::cout << "\nAvailable systems:\n";

        std::cout << "MathEngine\n";
        std::cout << "MemoryEngine\n";
        std::cout << "ObserverEngine\n";
        std::cout << "ArchiveEngine\n";
    }

    // --------------------------------------------
    // COMMAND PROCESSOR
    // --------------------------------------------

    void ProcessCommand(const std::string& command)
    {
        std::istringstream stream(command);

        std::string action;

        stream >> action;

        std::string payload;

        std::getline(stream, payload);

        if (!payload.empty() && payload[0] == ' ')
            payload.erase(0, 1);

        if (action == "help")
        {
            Help();
        }
        else if (action == "systems")
        {
            DiscoverSystems();
        }
        else if (action == "status")
        {
            Status();
        }
        else if (action == "send")
        {
            std::istringstream messageStream(payload);

            std::string destination;

            messageStream >> destination;

            std::string message;

            std::getline(messageStream, message);

            if (!message.empty() && message[0] == ' ')
                message.erase(0, 1);

            if (destination.empty() || message.empty())
            {
                std::cout << "Usage: send <system> <message>\n";
                return;
            }

            std::cout << "\n"
                      << Route(destination, message)
                      << "\n";
        }
        else if (action == "broadcast")
        {
            if (payload.empty())
            {
                std::cout << "Broadcast requires a message.\n";
                return;
            }

            Broadcast(payload);
        }
        else if (action == "weave")
        {
            if (payload.empty())
            {
                std::cout << "Weave requires an input.\n";
                return;
            }

            ExecuteWorkflow(payload);
        }
        else if (action == "calc")
        {
            std::cout << "\n"
                      << Route("MathEngine", payload)
                      << "\n";
        }
        else if (action == "remember")
        {
            std::cout << "\n"
                      << Route(
                          "MemoryEngine",
                          "remember " + payload
                      )
                      << "\n";
        }
        else if (action == "recall")
        {
            std::cout << "\n"
                      << Route("MemoryEngine", "recall")
                      << "\n";
        }
        else if (action == "log")
        {
            logger.Display();
        }
        else if (action == "quit")
        {
            std::cout << "\nOmniWeaver shutting down.\n";

            logger.Record("OmniWeaver shutdown.");

            running = false;
        }
        else if (action.empty())
        {
            return;
        }
        else
        {
            std::cout << "\nUnknown command. Type help.\n";
        }
    }

public:

    // --------------------------------------------
    // CONSTRUCTOR
    // --------------------------------------------

    OmniWeaver()
    {
        Register(std::make_unique<WeaverMath>());

        Register(std::make_unique<WeaverMemory>());

        Register(std::make_unique<WeaverObserver>());

        Register(std::make_unique<WeaverArchive>());
    }

    // --------------------------------------------
    // INITIALIZATION
    // --------------------------------------------

    void Initialize()
    {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "              OMNIWEAVER\n";
        std::cout << "       UNIVERSAL INTEGRATION CORE\n";
        std::cout << "========================================\n";

        std::cout << "\nVersion: "
                  << OmniCore::VERSION << "\n";

        std::cout << "\nDirective:\n"
                  << OmniCore::DIRECTIVE << "\n";

        std::cout << "\nInitializing subsystems...\n";

        DiscoverSystems();

        std::cout << "\nAll registered subsystems initialized.\n";

        logger.Record("OmniWeaver initialized.");

        running = true;
    }

    // --------------------------------------------
    // MAIN EXECUTION LOOP
    // --------------------------------------------

    void Run()
    {
        Initialize();

        std::string command;

        while (running)
        {
            std::cout << "\nOMNIWEAVER > ";

            if (!std::getline(std::cin, command))
                break;

            ProcessCommand(command);
        }

        std::cout << "\nCore execution terminated.\n";
    }
};

// ================================================
// APPLICATION ENTRY POINT
// ================================================

int main()
{
    try
    {
        OmniWeaver weaver;

        weaver.Run();
    }
    catch (const std::exception& error)
    {
        std::cerr << "\nCritical error: "
                  << error.what() << "\n";

        return 1;
    }

    return 0;
}
