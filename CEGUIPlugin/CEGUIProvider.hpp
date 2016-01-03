#include <CEGUI/CEGUI.h>
#include <d3d9.h>
#include <ElDorito/ElDorito.hpp>

namespace CEGUIPlugin
{
	class CEGUIProvider {
		bool loaded = false;

		void OnInit(void* param);
		void OnEndScene(void* param);
		LRESULT OnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		CEGUI::Key::Scan virtualkey2scancode(WPARAM wParam, LPARAM lParam);
	public:
		CEGUIProvider(IEngine* engine);
	};
}