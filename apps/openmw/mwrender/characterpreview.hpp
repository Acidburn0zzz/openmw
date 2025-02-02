#ifndef MWRENDER_CHARACTERPREVIEW_H
#define MWRENDER_CHARACTERPREVIEW_H

#include <osg/ref_ptr>
#include <memory>

#include <components/esm/loadnpc.hpp>

#include <components/resource/resourcesystem.hpp>

#include "../mwworld/ptr.hpp"

namespace osg
{
    class Texture2D;
    class Camera;
}

namespace osgViewer
{
    class Viewer;
}

namespace MWRender
{

    class NpcAnimation;
    class DrawOnceCallback;

    class CharacterPreview
    {
    public:
        CharacterPreview(osgViewer::Viewer* viewer, Resource::ResourceSystem* resourceSystem, MWWorld::Ptr character, int sizeX, int sizeY,
                         const osg::Vec3f& position, const osg::Vec3f& lookAt);
        virtual ~CharacterPreview();

        int getTextureWidth() const;
        int getTextureHeight() const;

        void redraw();

        void rebuild();

        osg::ref_ptr<osg::Texture2D> getTexture();

    private:
        CharacterPreview(const CharacterPreview&);
        CharacterPreview& operator=(const CharacterPreview&);

    protected:
        virtual bool renderHeadOnly() { return false; }
        virtual void onSetup();

        osg::ref_ptr<osgViewer::Viewer> mViewer;
        Resource::ResourceSystem* mResourceSystem;
        osg::ref_ptr<osg::Texture2D> mTexture;
        osg::ref_ptr<osg::Camera> mCamera;
        osg::ref_ptr<DrawOnceCallback> mDrawOnceCallback;

        osg::Vec3f mPosition;
        osg::Vec3f mLookAt;

        MWWorld::Ptr mCharacter;

        std::auto_ptr<MWRender::NpcAnimation> mAnimation;
        osg::ref_ptr<osg::PositionAttitudeTransform> mNode;
        std::string mCurrentAnimGroup;

        int mSizeX;
        int mSizeY;
    };

    class InventoryPreview : public CharacterPreview
    {
    public:

        InventoryPreview(osgViewer::Viewer* viewer, Resource::ResourceSystem* resourceSystem, MWWorld::Ptr character);

        void updatePtr(const MWWorld::Ptr& ptr);

        void update(); // Render preview again, e.g. after changed equipment
        void setViewport(int sizeX, int sizeY);

        int getSlotSelected(int posX, int posY);

    protected:
        virtual void onSetup();
    };

    class UpdateCameraCallback;

    class RaceSelectionPreview : public CharacterPreview
    {
        ESM::NPC                        mBase;
        MWWorld::LiveCellRef<ESM::NPC>  mRef;

    protected:

        virtual bool renderHeadOnly() { return true; }
        virtual void onSetup();

    public:
        RaceSelectionPreview(osgViewer::Viewer* viewer, Resource::ResourceSystem* resourceSystem);
        virtual ~RaceSelectionPreview();

        void setAngle(float angleRadians);

        const ESM::NPC &getPrototype() const {
            return mBase;
        }

        void setPrototype(const ESM::NPC &proto);

    private:

        osg::ref_ptr<UpdateCameraCallback> mUpdateCameraCallback;

        float mPitchRadians;
    };

}

#endif
