#include "Geometry.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Math;
using Ogre::ManualObject;
using Ogre::AxisAlignedBox;

ManualObject* Geometry::terrain(Real subdivision)
{
    ManualObject* manual = Global::getSceneManager()
        ->createManualObject();
    manual->begin(
        "BaseWhite",
        Ogre::RenderOperation::OT_LINE_LIST
    );

    for (long i=0;i<=subdivision;i++) {
        manual->position(-1,  1,  i*1/subdivision);
        manual->position(-1, -1,  i*1/subdivision);
        manual->position(-1,  1, -i*1/subdivision);
        manual->position(-1, -1, -i*1/subdivision);
        
        manual->position( 1,  1,  i*1/subdivision);
        manual->position( 1, -1,  i*1/subdivision);
        manual->position( 1,  1, -i*1/subdivision);
        manual->position( 1, -1, -i*1/subdivision);
        
        manual->position( 1, -1,  i*1/subdivision);
        manual->position(-1, -1,  i*1/subdivision);
        manual->position( 1, -1, -i*1/subdivision);
        manual->position(-1, -1, -i*1/subdivision);
        
        manual->position( 1,  1,  i*1/subdivision);
        manual->position(-1,  1,  i*1/subdivision);
        manual->position( 1,  1, -i*1/subdivision);
        manual->position(-1,  1, -i*1/subdivision);

        manual->position(-i*1/subdivision,  1, -1);
        manual->position(-i*1/subdivision, -1, -1);
        manual->position( i*1/subdivision,  1, -1);
        manual->position( i*1/subdivision, -1, -1);
        
        manual->position(-i*1/subdivision,  1,  1);
        manual->position(-i*1/subdivision, -1,  1);
        manual->position( i*1/subdivision,  1,  1);
        manual->position( i*1/subdivision, -1,  1);

        manual->position(-i*1/subdivision,  1,  1);
        manual->position(-i*1/subdivision,  1, -1);
        manual->position( i*1/subdivision,  1,  1);
        manual->position( i*1/subdivision,  1, -1);

        manual->position(-i*1/subdivision, -1,  1);
        manual->position(-i*1/subdivision, -1, -1);
        manual->position( i*1/subdivision, -1,  1);
        manual->position( i*1/subdivision, -1, -1);

        manual->position( 1, -i*1/subdivision, -1);
        manual->position(-1, -i*1/subdivision, -1);
        manual->position( 1,  i*1/subdivision, -1);
        manual->position(-1,  i*1/subdivision, -1);

        manual->position( 1, -i*1/subdivision,  1);
        manual->position(-1, -i*1/subdivision,  1);
        manual->position( 1,  i*1/subdivision,  1);
        manual->position(-1,  i*1/subdivision,  1);

        manual->position( 1, -i*1/subdivision,  1);
        manual->position( 1, -i*1/subdivision, -1);
        manual->position( 1,  i*1/subdivision,  1);
        manual->position( 1,  i*1/subdivision, -1);

        manual->position(-1, -i*1/subdivision,  1);
        manual->position(-1, -i*1/subdivision, -1);
        manual->position(-1,  i*1/subdivision,  1);
        manual->position(-1,  i*1/subdivision, -1);
    }
    manual->end();
    manual->setBoundingBox(
        AxisAlignedBox(-1, -1, -1, 1, 1, 1));

    return manual;
}

ManualObject* Geometry::cylinder(Real subdivision)
{
    ManualObject* manual = Global::getSceneManager()
        ->createManualObject();
    manual->begin(
        "BaseWhite",
        Ogre::RenderOperation::OT_TRIANGLE_LIST
    );

    for (Real i=0.0;
        i<1.0+1.0/subdivision;
        i+=1.0/subdivision
    ) {
        Real c1 = Math::Cos(i*3.14*2.0);
        Real s1 = Math::Sin(i*3.14*2.0);
        Real c2 = Math::Cos((i+1.0/subdivision)*3.14*2.0);
        Real s2 = Math::Sin((i+1.0/subdivision)*3.14*2.0);
        for (Real j=-1.0;j<=1.0;j+=1.0/subdivision) {
            manual->position(j+1.0/subdivision, c1, s1);
            manual->normal(0, c1, s1);
            manual->position(j, c1, s1);
            manual->normal(0, c1, s1);
            manual->position(j+1.0/subdivision, c2, s2);
            manual->normal(0, c2, s2);
            manual->position(j, c2, s2);
            manual->normal(0, c2, s2);
            manual->position(j+1.0/subdivision, c2, s2);
            manual->normal(0, c2, s2);
            manual->position(j, c1, s1);
            manual->normal(0, c1, s1);
        }
        manual->position(1, 0, 0);
        manual->normal(1, 0, 0);
        manual->position(1, c1, s1);
        manual->normal(1, 0, 0);
        manual->position(1, c2, s2);
        manual->normal(1, 0, 0);
        manual->position(-1, c1, s1);
        manual->normal(-1, 0, 0);
        manual->position(-1, 0, 0);
        manual->normal(-1, 0, 0);
        manual->position(-1, c2, s2);
        manual->normal(-1, 0, 0);
    }

    manual->end();
    manual->setBoundingBox(
        AxisAlignedBox(-1, -1, -1, 1, 1, 1));

    return manual;
}

ManualObject* Geometry::diamond()
{
    ManualObject* manual = Global::getSceneManager()
        ->createManualObject();
    manual->begin(
        "BaseWhite",
        Ogre::RenderOperation::OT_TRIANGLE_LIST
    );

    manual->position(1, 0, 0);
    manual->normal(1, 0, 0);
    manual->position(0, 1, 0); 
    manual->normal(0, 1, 0);
    manual->position(0, 0, 1); 
    manual->normal(0, 0, 1);

    manual->position(0, 0, 1); 
    manual->normal(0, 0, 1); 
    manual->position(0, 1, 0); 
    manual->normal(0, 1, 0); 
    manual->position(-1, 0, 0); 
    manual->normal(-1, 0, 0); 
    
    manual->position(-1, 0, 0); 
    manual->normal(-1, 0, 0); 
    manual->position(0, 1, 0); 
    manual->normal(0, 1, 0); 
    manual->position(0, 0, -1); 
    manual->normal(0, 0, -1); 
    
    manual->position(0, 0, -1); 
    manual->normal(0, 0, -1); 
    manual->position(0, 1, 0); 
    manual->normal(0, 1, 0); 
    manual->position(1, 0, 0); 
    manual->normal(1, 0, 0); 
    
    manual->position(0, -1, 0); 
    manual->normal(0, -1, 0); 
    manual->position(1, 0, 0); 
    manual->normal(1, 0, 0); 
    manual->position(0, 0, 1); 
    manual->normal(0, 0, 1); 

    manual->position(0, -1, 0); 
    manual->normal(0, -1, 0); 
    manual->position(0, 0, 1); 
    manual->normal(0, 0, 1); 
    manual->position(-1, 0, 0); 
    manual->normal(-1, 0, 0); 
    
    manual->position(0, -1, 0); 
    manual->normal(0, -1, 0); 
    manual->position(-1, 0, 0); 
    manual->normal(-1, 0, 0); 
    manual->position(0, 0, -1); 
    manual->normal(0, 0, -1); 
    
    manual->position(0, -1, 0); 
    manual->normal(0, -1, 0); 
    manual->position(0, 0, -1); 
    manual->normal(0, 0, -1); 
    manual->position(1, 0, 0); 
    manual->normal(1, 0, 0); 

    manual->end();
    manual->setBoundingBox(
        AxisAlignedBox(-1, -1, -1, 1, 1, 1));

    return manual;
}

ManualObject* Geometry::sphere(Real subdivision)
{
    ManualObject* manual = Global::getSceneManager()
        ->createManualObject();
    manual->begin(
        "BaseWhite",
        Ogre::RenderOperation::OT_TRIANGLE_LIST
    );

    for (Real i=-1.0;i<=1.0;i+=1.0/subdivision) {
        for (Real j=0.0;
            j<=1.0+1.0/subdivision;
            j+=1.0/subdivision
        ) {
            Real c1 = Math::Cos(j*2.0*3.14);
            Real s1 = Math::Sin(j*2.0*3.14);
            Real c2 = Math::Cos((j+1.0/subdivision)*2.0*3.14);
            Real s2 = Math::Sin((j+1.0/subdivision)*2.0*3.14);
            Real r1 = Math::Sin(
                Math::ACos(Math::Abs(i)));
            Real r2 = Math::Sin(
                Math::ACos(Math::Abs(i+1.0/subdivision)));
            //Real r1 = 1-Math::Abs(i);
            //r1 *= r1;
            //Real r2 = 1-Math::Abs(i+1.0/subdivision);
            //r2 *= r2;

            manual->position(r1*c2, i, r1*s2);
            manual->normal(r1*c2, i, r1*s2);
            manual->position(r1*c1, i, r1*s1);
            manual->normal(r1*c1, i, r1*s1);
            manual->position(r2*c2, i+1.0/subdivision, r2*s2);
            manual->normal(r2*c2, i+1.0/subdivision, r2*s2);

            manual->position(r2*c1, i+1.0/subdivision, r2*s1);
            manual->normal(r2*c1, i+1.0/subdivision, r2*s1);
            manual->position(r2*c2, i+1.0/subdivision, r2*s2);
            manual->normal(r2*c2, i+1.0/subdivision, r2*s2);
            manual->position(r1*c1, i, r1*s1);
            manual->normal(r1*c1, i, r1*s1);
        }
    }

    manual->end();
    manual->setBoundingBox(
        AxisAlignedBox(-1, -1, -1, 1, 1, 1));

    return manual;
}

