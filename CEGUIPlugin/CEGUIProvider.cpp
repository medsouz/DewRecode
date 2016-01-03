#include "CEGUIProvider.hpp"

#include <CEGUI/RendererModules/Direct3D9/Renderer.h>

namespace CEGUIPlugin
{
	CEGUIProvider::CEGUIProvider(IEngine* engine)
	{
		engine->OnEvent("Core", "Direct3D.Init", BIND_CALLBACK(this, &CEGUIProvider::OnInit));
		engine->OnEndScene(BIND_CALLBACK(this, &CEGUIProvider::OnEndScene));
		engine->OnWndProc(BIND_WNDPROC(this, &CEGUIProvider::OnWndProc));
	}

	void CEGUIProvider::OnInit(void* param)
	{
		//Create CEGUI Renderer
		CEGUI::Direct3D9Renderer& renderer = CEGUI::Direct3D9Renderer::bootstrapSystem(Pointer(0x50DADDC).Read<IDirect3DDevice9*>());
		//Configure CEGUI directories
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("schemes", "./CEGUI/schemes/");
		rp->setResourceGroupDirectory("imagesets", "./CEGUI/imagesets/");
		rp->setResourceGroupDirectory("fonts", "./CEGUI/fonts/");
		rp->setResourceGroupDirectory("layouts", "./CEGUI/layouts/");
		rp->setResourceGroupDirectory("looknfeels", "./CEGUI/looknfeel/");
		rp->setResourceGroupDirectory("schemas", "./CEGUI/xml_schemas/");
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");

		//Theme stuff
		CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
		CEGUI::SchemeManager::getSingleton().createFromFile("ElDewrito.scheme");

		//Test window
		CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MainMenu.layout");
		myRoot->setHorizontalAlignment(CEGUI::HorizontalAlignment::HA_CENTRE);
		myRoot->setVerticalAlignment(CEGUI::VerticalAlignment::VA_CENTRE);
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

		loaded = true;
	}

	void CEGUIProvider::OnEndScene(void* param)
	{
		CEGUI::System::getSingleton().renderAllGUIContexts();
	}

	LRESULT CEGUIProvider::OnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (!loaded)
			return 0;

		CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			context.injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
			break;
		case WM_LBUTTONUP:
			context.injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
			break;
		case WM_RBUTTONDOWN:
			context.injectMouseButtonDown(CEGUI::MouseButton::RightButton);
			break;
		case WM_RBUTTONUP:
			context.injectMouseButtonUp(CEGUI::MouseButton::RightButton);
			break;
		case WM_MOUSEWHEEL:
			context.injectMouseWheelChange(GET_WHEEL_DELTA_WPARAM(wParam));
			break;
		case WM_MOUSEMOVE:
			context.injectMousePosition((signed short)(lParam), (signed short)(lParam >> 16));
			break;
		case WM_KEYDOWN:
			context.injectKeyDown(virtualkey2scancode(wParam, lParam));
			break;
		case WM_KEYUP:
			context.injectKeyUp(virtualkey2scancode(wParam, lParam));
			break;
		case WM_CHAR:
			context.injectChar(static_cast<CEGUI::utf32>(wParam));
			break;
		}
		return 0;
	}

	//Converts Win32 input into CEGUI compatible input
	CEGUI::Key::Scan CEGUIProvider::virtualkey2scancode(WPARAM wParam, LPARAM lParam)
	{
		if (HIWORD(lParam) & 0x0F00)
		{
			UINT scancode = MapVirtualKey(wParam, 0);
			return static_cast<CEGUI::Key::Scan>(scancode | 0x80);
		}
		else
		{
			return static_cast<CEGUI::Key::Scan>(HIWORD(lParam) & 0x00FF);
		}
	}
}
