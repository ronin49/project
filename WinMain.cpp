#include <d3d11.h>
#include <Windows.h>
#include <ctime>
#include <string>

#pragma comment(lib,"d3d11.lib")

std::wstring title = L"title";
std::wstring mytime = L"title";

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_CLOSE) {
		PostQuitMessage(69);
		//DestroyWindow(hWnd);
	}
	if (msg == WM_MOUSEMOVE) {
		POINTS pt = MAKEPOINTS(lParam);
		title = std::to_wstring(pt.x) + L"," + std::to_wstring(pt.y);
		SetWindowText(hWnd, (title + mytime).c_str());
		//MessageBox(hWnd, L"hare!!", L"hare!!!!!!!!", MB_OK
		//ShowWindow(hWnd, SW_HIDE);
	}
	if (msg == WM_KILLFOCUS) {
		PostQuitMessage(69);
	}
	if (msg == WM_CHAR) {
		static std::wstring title;
		title += (char)wParam;
	}

	//OutputDebugString(L"dsa");
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow
) {

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"lolkekcheburek";
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindowEx(
		0,
		L"lolkekcheburek",
		std::wstring(L"happy hard window lol kek").c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		640, 480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	ShowWindow(hWnd, SW_SHOW);

	MSG msg;

	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
	ID3D11Resource* pBackBuffer = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);

	auto timer = std::clock();
	auto dt = std::clock() - std::clock();
	while (true) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//dt += std::clock() - timer; timer = std::clock();
		//while (dt >= CLOCKS_PER_SEC / 60) {
			//dt -= CLOCKS_PER_SEC / 60;
			static int i = 0; i++;
			mytime = std::to_wstring(i);
			SetWindowText(hWnd, (title + mytime).c_str());

			const float color[] = { 1, 0, 0, 1 };
			pContext->ClearRenderTargetView(pTarget, color);
			pSwap->Present(1u, 0u);
		//}
		if (IsWindow(hWnd) == false)break;
	}
	return 0;
}
