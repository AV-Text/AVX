#include "pch.h"
#include "AVXHistory.h"
#if __has_include("AVXHistory.g.cpp")
#include "AVXHistory.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::AVXSearch::implementation
{
    int32_t AVXHistory::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AVXHistory::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AVXHistory::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
