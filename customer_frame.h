#ifndef CUSTOMER_FRAME_H
#define CUSTOMER_FRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "customer.h"
#include "login_frame.h"

class CustomerFrame : public wxFrame {
public:
    CustomerFrame(const wxString& title, int userId);
    ~CustomerFrame();
