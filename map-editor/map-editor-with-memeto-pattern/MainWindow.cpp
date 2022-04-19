#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE hInst) :
	hInst(hInst),
	dwStyle(WS_OVERLAPPEDWINDOW),
	width(CW_USEDEFAULT),
	height(CW_USEDEFAULT),
	windowTitle(nullptr),
	hMainWnd(nullptr) {

}

MainWindow::~MainWindow() { }

bool MainWindow::setup() {
	LPCTSTR className = _T("MyMainWindow");
	WNDCLASSEX wcex;

	::ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);

	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = &MainWindow::winProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInst;
	wcex.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hIconSm = ::LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcex.lpszClassName = className;
	wcex.lpszMenuName = nullptr;

	if (!::RegisterClassEx(&wcex)) {
		DWORD dwError = ::GetLastError(); // TODO: error handling
		return false;
	}

	this->hMainWnd = ::CreateWindowEx(
		0,
		className,
		this->windowTitle ? this->windowTitle : _T("Hello World"),
		this->dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, this->width, this->height,
		nullptr,
		nullptr,
		this->hInst,
		this
	);

	setupEventRoute();

	if (hMainWnd == nullptr) {
		DWORD dwError = ::GetLastError(); // TODO: error handling
		return false;
	}

	// if this->width == CW_USEDEFAULT || this->height == CW_USEDEFAULT, get real size
	RECT rc;
	::GetWindowRect(hMainWnd, &rc);
	this->width = rc.right - rc.left;
	this->height = rc.bottom - rc.top;

	return true;
}

bool MainWindow::canShowWindow() {
	return this->hMainWnd != nullptr;
}

void MainWindow::showWindow() {
	if (this->canShowWindow()) {
		::ShowWindow(this->hMainWnd, SW_NORMAL);
		::UpdateWindow(this->hMainWnd);
	}
}

void MainWindow::peekingMessage() {
	auto msgPtr = &(this->peekedMsg);
	if (::PeekMessage(msgPtr, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(msgPtr);
		::DispatchMessage(msgPtr);
	}
}

bool MainWindow::isReceivedMessage(UINT msg) {
	return this->peekedMsg.message == msg;
}

bool MainWindow::needQuit() {
	return this->isReceivedMessage(WM_QUIT);
}

void MainWindow::addEventRoute(UINT msg, Action action) {
	Handler it = this->eventRouter.find(msg);
	if (it == this->eventRouter.end()) {
		std::vector<Action> handlers;
		handlers.push_back(action);
		this->eventRouter.insert(std::make_pair(msg, handlers));
	}
	else {
		it->second.push_back(action);
	}
}

const MSG* const MainWindow::getPeekedMessage() const {
	return &this->peekedMsg;
}
