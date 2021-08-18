#include "Overlay.h"
#include "Application.h"

Overlay::Overlay()
{ 
    int glt = gltInit();
    m_OverlayData = new OverlayData();
    field = gltCreateText();
}

void Overlay::Render(OVERLAY_STATE OverlayState)
{
    gltBeginDraw();
    char str[64];
    float ZOffset = 30;
    if (!OverlayState == OVERLAY_STATE::S_FPS_ONLY)
    {
        gltColor(1, 0, 0, 1);
        {
            sprintf_s(str, "Triangles: %d", m_OverlayData->TriCount);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            sprintf_s(str, "Lights: %d", m_OverlayData->LightCount);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 2 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            sprintf_s(str, "Depth Buffering: %d", m_OverlayData->DepthBuffering);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 3 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            sprintf_s(str, "Back Face Culling: %d", m_OverlayData->BackFaceCulling);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 4 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            int x = m_OverlayData->Resolution.x;
            int y = m_OverlayData->Resolution.y;
            int ref = m_OverlayData->RefreshRate;
            sprintf_s
            (
                str,
                "Resolution: %d x %d, %d Hz",
                x,
                y, 
                ref
            );
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 5 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            sprintf_s(str, "Scene: %d", m_OverlayData->SceneNumber);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 6 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            sprintf_s(str, "Subdivisions: %d", m_OverlayData->LOD);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 7 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
        {
            sprintf_s(str, "Geometry Size: %llu bytes", m_OverlayData->GeometrySize);
            gltSetText(field, str);
            gltDrawText2DAligned
            (
                field,
                0,
                Application::Get().GetWindow().m_Data.Height - 8 * ZOffset,
                1.0f,
                GL_LEFT,
                GLT_BOTTOM
            );
        }
    }
    // FPS ONLY
    gltColor(1, 0, 0, 1);
    { 
        sprintf_s(str, "FPS: %.2f", Application::Get().GetUtils().m_FPS);
        gltSetText(field, str);
        gltDrawText2DAligned
        (
            field,
            0, 
            Application::Get().GetWindow().m_Data.Height, 
            1.0f, 
            GL_LEFT, 
            GLT_BOTTOM
        );
    }
    gltEndDraw();
}

void Overlay::End()
{
    gltDeleteText(field);
    gltTerminate();
}
