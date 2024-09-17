#include <windows.h>
#include <iostream>
#include <string>

void ConfigureSerialPort(HANDLE hSerial)
{
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting the current serial port state." << std::endl;
        return;
    }

    dcbSerialParams.BaudRate = CBR_2400;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting the serial port parameters." << std::endl;
        return;
    }

    if (!SetupComm(hSerial, 4096, 4096)) { // Increase buffer size
        std::cerr << "Error setting up serial port buffers." << std::endl;
        return;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 100;
    timeouts.ReadTotalTimeoutConstant = 200;
    timeouts.ReadTotalTimeoutMultiplier = 50;
    timeouts.WriteTotalTimeoutConstant = 200;
    timeouts.WriteTotalTimeoutMultiplier = 50;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error setting timeouts." << std::endl;
        return;
    }

    if (!PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR)) {
        std::cerr << "Error flushing serial port buffers." << std::endl;
        return;
    }
}

void WriteToSerialPort(HANDLE hSerial, const std::string& data)
{
    DWORD bytesWritten;

    DWORD startTime = GetTickCount();

    if (!WriteFile(hSerial, data.c_str(), data.size(), &bytesWritten, NULL)) {
        std::cerr << "Error writing to serial port." << std::endl;
    } else {
        DWORD endTime = GetTickCount();
        DWORD duration = endTime - startTime;

        double transmissionSpeed = (data.size() / (duration / 1000.0)); // bytes per second
        double transmissionSpeedBps = transmissionSpeed * 8; // bits per second

        std::cout << "\nData sent: " << data << std::endl;
        std::cout << "Transmission time: " << duration << " ms" << std::endl;
        std::cout << "Transmission speed: " << transmissionSpeed << " Bps (" << transmissionSpeedBps << " bps)" << std::endl;
    }
}

void ReadFromSerialPort(HANDLE hSerial, int bytesToRead)
{
    char *buffer = new char[bytesToRead + 1];
    DWORD bytesRead;
    int totalBytesRead = 0;
    bool success = true;

    DWORD startTime = GetTickCount();

    while (totalBytesRead < bytesToRead) {
        DWORD bytesRemaining = bytesToRead - totalBytesRead;
        if (ReadFile(hSerial, buffer + totalBytesRead, bytesRemaining, &bytesRead, NULL)) {
            totalBytesRead += bytesRead;
            if (bytesRead == 0) {
                break;
            }
        } else {
            std::cerr << "Error reading from serial port." << std::endl;
            success = false;
            break;
        }
    }

    DWORD endTime = GetTickCount();
    DWORD duration = endTime - startTime;

    if (success) {
        buffer[totalBytesRead] = '\0';
        double receptionSpeed = (totalBytesRead / (duration / 1000.0));
        double receptionSpeedBps = receptionSpeed * 8; // bits per second

        std::cout << "Data received (" << totalBytesRead << " bytes): " << buffer << std::endl;
        std::cout << "Reception time: " << duration << " ms" << std::endl;
        std::cout << "Reception speed: " << receptionSpeed << " Bps (" << receptionSpeedBps << " bps)" << std::endl;
    }

    delete[] buffer;
}

int main()
{
    const char *portName = "COM6"; // Use COM6 as the port
    HANDLE hSerial = CreateFile(portName,
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening COM port." << std::endl;
        return 1;
    }

    ConfigureSerialPort(hSerial);

    std::string dataToSend = 
        "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, "
        "saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, "
        "in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. "
        "Government should focus on sources of the next crisis, not just the last one.\n"
        "In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate "
        "due diligence, creating the environment for future NPAs,\" Rajan said in the note.\" Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be "
        "examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently.";

    WriteToSerialPort(hSerial, dataToSend);
    std::cout << "" << std::endl;

    int bytesToReceive = 1010;
    ReadFromSerialPort(hSerial, bytesToReceive);

    CloseHandle(hSerial);
    return 0;
}
