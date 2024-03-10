#pragma once

#include <thread>
#include <codecvt>

#include <EBEventLoop.hpp>
#include <EBNuklear.hpp>
#include <EBNuklearRow.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearWindow : public EBNuklearWidget
    {
    public:
        EBNuklearWindow(int32_t width, int32_t height, EBString title) : title(title), wnd(0), font(nullptr), ctx(nullptr), width(width), height(height), running(true),
                                                         windowThread(std::thread(&EBNuklearWindow::createWindow, this)), centralWidget(nullptr)
        {
            windowCount++;
        }

        virtual ~EBNuklearWindow()
        {
            windowCount--;
        }

        void setFont(EBCpp::EBString font, int size)
        {
            if (this->font)
            {
                nk_gdifont_del(this->font);
            }
            this->font = nk_gdifont_create(font.dataPtr(), size);
            nk_gdi_set_font(this->font);
        }

        EBPtr<EBNuklearWidget> setCentralWidget(const EBPtr<EBNuklearWidget> centralWidget)
        {
            centralWidget->setParent(this);
            this->centralWidget = centralWidget;
            return centralWidget;
        }

        EBPtr<EBNuklearWidget> getCentralWidget() const
        {
            return centralWidget;
        }

        virtual void invalidate() override
        {
            PostMessage(wnd, WM_USER, 0, 0);
        }

        virtual void render(struct nk_context *ctx) const
        {
            if (nk_begin(ctx, "Nuklear", nk_rect(0, 0, (float)width, (float)height), 0))
            {
                if( centralWidget != nullptr )
                {
                    centralWidget->render(ctx);
                }
            }
            nk_end(ctx);

            nk_gdi_render(nk_rgb(30, 30, 30));            
        }

    protected:

        virtual void createWindow()
        {            
            RECT rect = {0, 0, width, height};
            DWORD style = WS_OVERLAPPEDWINDOW;
            DWORD exstyle = WS_EX_APPWINDOW;

            /* Win32 */
            WNDCLASSA wc;
            memset(&wc, 0, sizeof(wc));
            wc.style = CS_DBLCLKS;
            wc.hInstance = GetModuleHandleW(0);
            wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON1));
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.lpszClassName = "NuklearWindowClass";
            wc.lpfnWndProc = &EBNuklearWindow::windowProcBase;
            RegisterClassA(&wc);

            AdjustWindowRectEx(&rect, style, FALSE, exstyle);

            wnd = CreateWindowExA(exstyle, wc.lpszClassName, title.dataPtr(),
                                  style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                                  rect.right - rect.left, rect.bottom - rect.top,
                                  nullptr, nullptr, wc.hInstance, nullptr);

            SetWindowLongPtr(wnd, GWLP_USERDATA, (LONG_PTR)(this));

            HICON icon = LoadIcon(GetModuleHandleW(0), MAKEINTRESOURCE(IDI_ICON1));
            SendMessage(wnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
            SendMessage(wnd, WM_SETICON, ICON_BIG, (LPARAM)icon);

            dc = GetDC(wnd);

            setFont("Arial", 18);

            /* GUI */
            ctx = nk_gdi_init(font, dc, width, height);

            while (running)
            {
                doInputs();
                render(ctx);
            }

            nk_gdifont_del(font);
            nk_gdi_shutdown();

            DestroyWindow(wnd);
        }

        virtual void doInputs()
        {
            /* Input */
            MSG msg;
            nk_input_begin(ctx);
            if (needs_refresh == 0)
            {
                if (GetMessageW(&msg, NULL, 0, 0) <= 0)
                {
                    running = false;
                }
                else
                {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
                needs_refresh = true;
            }
            else
                needs_refresh = false;

            while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                    running = false;
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
                needs_refresh = true;
            }
            nk_input_end(ctx);
        }

    private:
        static LRESULT CALLBACK windowProcBase(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
        {
            EBNuklearWindow *pThis = reinterpret_cast<EBNuklearWindow *>(GetWindowLongPtr(wnd, GWLP_USERDATA));
            if (pThis != nullptr)
                return pThis->windowProc(wnd, msg, wparam, lparam);
            else
                return DefWindowProc(wnd, msg, wparam, lparam);
            ;
        }

        LRESULT windowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
        {
            switch (msg)
            {
            case WM_DESTROY:
                if (windowCount == 1)
                {
                    EBCpp::EBEventLoop::getInstance()->exit();
                }
                PostQuitMessage(0);
                running = false;
                return 0;

            case WM_SIZE:
                width = LOWORD(lparam);
                height = HIWORD(lparam);
                break;

            default:
                break;
            }

            if (nk_gdi_handle_event(wnd, msg, wparam, lparam))
                return 0;
            return DefWindowProcW(wnd, msg, wparam, lparam);
        }

        static inline int windowCount = 0;

        // GDI Parameter
        GdiFont *font;
        HDC dc;
        HWND wnd;

        // Window Data
        EBString title;
        struct nk_context *ctx;
        int width;
        int height;
        bool running;
        bool needs_refresh;
        std::thread windowThread;

        EBPtr<EBNuklearWidget> centralWidget;
    };
}
