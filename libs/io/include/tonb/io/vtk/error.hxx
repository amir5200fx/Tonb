//
// Created by amir on 8/28/25.
//
#pragma once
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkObject.h>
#include <vtkSmartPointer.h>

#include <stdexcept>
#include <string>

class ErrorToException {
public:
    explicit ErrorToException(vtkObject* obj) : obj_(obj) {
        callback_ = vtkSmartPointer<vtkCallbackCommand>::New();
        callback_->SetCallback(&ErrorToException::on_error);
        callback_->SetClientData(this);
        obj_->AddObserver(vtkCommand::ErrorEvent, callback_);
    }
private:
    static void on_error(vtkObject*, unsigned long, void* client_data, void* cell_data) {
        const auto msg = static_cast<const char*>(cell_data);
        throw std::runtime_error(std::string("VTK error: ") + (msg ? std::string(msg) : ""));
    }
    vtkObject* obj_{nullptr};
    vtkSmartPointer<vtkCallbackCommand> callback_{nullptr};
};