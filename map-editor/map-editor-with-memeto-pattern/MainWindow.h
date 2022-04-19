#pragma once

#include <Windows.h>
#include <unordered_map>
#include <vector>
#include <functional>
#include <tchar.h>
#include "util.h"

class MainWindow {
	typedef MainWindow Me;
	typedef std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> Action;
	typedef std::unordered_map<UINT, std::vector<Action>> EventRouter;
	typedef typename EventRouter::iterator Handler;

public:
	MainWindow(HINSTANCE hInst);
	~MainWindow();

	bool setup();
	bool canShowWindow();
	void showWindow();
	void peekingMessage();
	bool isReceivedMessage(UINT msg);
	bool needQuit();

	void addEventRoute(UINT msg, Action action);

	const MSG* const getPeekedMessage() const;

private:
	static LRESULT CALLBACK winProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		MainWindow* pWin = nullptr;
		if (uMsg == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pWin = reinterpret_cast<MainWindow*>(lpcs->lpCreateParams);

			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(pWin));
		}
		else {
			pWin = reinterpret_cast<MainWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}

		if (pWin != nullptr) {
			return pWin->handleEvent(hWnd, uMsg, wParam, lParam);
		}

		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void setupEventRoute() {
		addEventRoute(WM_DESTROY, TO_WINDOW_PROC_LAMBDA(this, onDestroy));
	}

	LRESULT onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		// Post WM_QUIT message to thread's message queue.
		::PostQuitMessage(0);
		return 0;
	}

	LRESULT handleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		auto handlers = eventRouter[uMsg];
		if (!handlers.empty()) {
			LRESULT res = 0;
			for (auto it = handlers.begin(); it != handlers.end(); it++) {
				res = (*it)(hWnd, uMsg, wParam, lParam);
				if (res != 0) {
					return res;
				}
			}

			return res;
		}

		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}



protected:
	HINSTANCE hInst;
	HWND hMainWnd;
	MSG peekedMsg;

	int width;
	int height;
private:
	LPTSTR windowTitle;
	DWORD dwStyle;
	EventRouter eventRouter;
};

