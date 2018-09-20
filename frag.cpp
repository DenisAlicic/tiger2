#include "frag.hpp"

using namespace frag;

Frag::Frag()
	: m_next(nullptr)
{}

DataFrag::DataFrag(temp::Label* label, std::string data)
	: m_label(label), m_data(std::move(data))
{}

ProcFrag::ProcFrag(tree::Stm* body, frame::Frame* frame)
	: m_body(body), m_frame(frame)
{}
