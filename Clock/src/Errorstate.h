#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include <functional>
#include <map>

#include "common.h"

// Error codes
enum class ErrorCode {
    NONE,
    WIFI_DISCONNECTED,
    TIME_NOT_SYNCED
};

// Error handler callback type
using ErrorHandlerCallback = std::function<void(ErrorCode)>;

class ErrorState {
public:
    ErrorState() {
        // Initialize error handler callbacks
        _errorHandlers[ErrorCode::WIFI_DISCONNECTED] = nullptr;
        _errorHandlers[ErrorCode::TIME_NOT_SYNCED] = nullptr;
    }

    void checkForErrors() {
        // Check for WiFi connection
        if (WiFi.status() != WL_CONNECTED) {
            setError(ErrorCode::WIFI_DISCONNECTED);
        } else {
            clearError(ErrorCode::WIFI_DISCONNECTED);
        }

        // Check for time sync
        time_t now;
        time(&now);
        if (now < 1609459200) { // January 1, 2021
            setError(ErrorCode::TIME_NOT_SYNCED);
        } else {
            clearError(ErrorCode::TIME_NOT_SYNCED);
        }
    }

    void setErrorHandler(ErrorCode code, ErrorHandlerCallback callback) {
        _errorHandlers[code] = callback;
    }

private:
    void setError(ErrorCode code) {
        if (!_errorFlags[code]) {
            _errorFlags[code] = true;
            if (_errorHandlers[code]) {
                _errorHandlers[code](code);
            }
        }
    }

    void clearError(ErrorCode code) {
        if (_errorFlags[code]) {
            _errorFlags[code] = false;
        }
    }

    std::map<ErrorCode, bool> _errorFlags;
    std::map<ErrorCode, ErrorHandlerCallback> _errorHandlers;
};

#endif // ERRORSTATE_H