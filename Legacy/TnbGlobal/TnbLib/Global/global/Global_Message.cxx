#include <Global_Message.hxx>

std::shared_ptr<tnbLib::Global_Message> tnbLib::gl_messenger = 
std::make_shared<tnbLib::Global_MessageOstream>();