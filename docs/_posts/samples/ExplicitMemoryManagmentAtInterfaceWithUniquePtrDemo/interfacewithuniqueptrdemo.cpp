//
// Demo using std::unique_ptr to improve a C++03 interface taking owning
// raw pointers (without improving the implementation for now)
//
// The new interface is the wrapper templace function ObjectManager::AddObject
// around the existing overloaded interface that uses raw owning pointer
//

#include <vector>
#include <memory>
#include <assert.h>

class BaseObject;
class ObjectManager;
std::unique_ptr< ObjectManager > sm_manager = nullptr;

////////////////////////////////////////////////////////////////////////////////
//
// Managed Object classes
//
////////////////////////////////////////////////////////////////////////////////

enum class Setting {All, Nothing};

class BaseObject{
public:
    virtual ~BaseObject() {}
};

class DerivedObject : public BaseObject
{
public:
    void SetSetting( Setting setting ) {}
};

////////////////////////////////////////////////////////////////////////////////
//
// Object managment with explicit lifetime.
// AddObject gain safe overload
//
////////////////////////////////////////////////////////////////////////////////
class ObjectManager
{
public:
    // New explicit interface
    template< typename ObjectT >
    ObjectT& AddObject( std::unique_ptr< ObjectT > object )
    {
        // Enforced:
        // if throw, object is destroyed
        // otherwise the memory is now managed by ObjectManager

        assert( object );
        AddObject( object.get() );
        return *object.release(); // succeed: Now managed by ObjectManager
    }

    // Legacy interface (deprecated)
    void AddObject( BaseObject* object )
    {
        // Understood convention:
        // if throw: caller needs to delete siteObj.
        // otherwise the memory is now managed by ObjectManager.

        CheckValid( object );
        m_objects.push_back( object );
    }

    // Legacy memory managment
    ~ObjectManager()
    {
        for ( auto obj : m_objects )
        {
            delete obj;
        }
    }

private:
    void CheckValid( BaseObject* object )
    {
       // throw if not valid
    }

private:
   // Legacy memory managment
   std::vector< BaseObject* > m_objects;
};

void DoSomethingThatMayThrow()
{
    // something that may throw
}

////////////////////////////////////////////////////////////////////////////////
//
// Example with legacy interface.
//
////////////////////////////////////////////////////////////////////////////////

// OK use of the raw pointer interface.
void AddDerivedManualManagment()
{
    DerivedObject* object = new DerivedObject();
    try
    {
        sm_manager->AddObject( object );
    }
    catch ( ... )
    {
        delete object;
        throw;
    }
}

// Incorrect use of the raw pointer interface.
void AddDerivedManualManagmentUnsafe()
{
    DerivedObject* object = new DerivedObject();
    try
    {
        sm_manager->AddObject( object );
        DoSomethingThatMayThrow(); // if this throw object will be deleted twice.
    }
    catch ( ... )
    {
        delete object;
        throw;
    }
}

// Incorrect use of std::unique_ptr relase()
//
// unique_ptr relase() indicate manual memory management and is dangerous.
// Prefer delegating this to dedicated function like the new AddObject
void AddDerivedManualManagmentWithUniquePtrUnsafe()
{
    auto object = std::make_unique< DerivedObject >();

    sm_manager->AddObject( object.get() );
    DoSomethingThatMayThrow(); // if this throw object will be deleted twice.
    object.release();
}


////////////////////////////////////////////////////////////////////////////////
//
// Example with new explicit interface with unique_ptr.
//
////////////////////////////////////////////////////////////////////////////////

void AddDerivedSimple()
{
    sm_manager->AddObject(
        std::make_unique< DerivedObject >()
        );
    DoSomethingThatMayThrow();
}

void AddDerivedWithSettingBefore( Setting setting )
{
    auto object = std::make_unique< DerivedObject >();
    object->SetSetting( setting );

    sm_manager->AddObject(
        std::move( object ) // object can only be assigned or destroyed after
                            // this or Undefined Behavior
        );
    DoSomethingThatMayThrow();
}

void AddDerivedWithSettingBeforeNoMove( Setting setting )
{
    // This lambda could also be a normal named function or use capture.
    auto makeDerivedWithSetting = []( Setting setting )
    {
        auto object = std::make_unique< DerivedObject >();
        object->SetSetting( setting );
        return object;
    };

    sm_manager->AddObject(
        makeDerivedWithSetting( setting ) // No need for std::move
                                          // No unsafe variable left behind
        );
    DoSomethingThatMayThrow();
}

void AddDerivedWithSettingAfter( Setting setting )
{
    DerivedObject& object = sm_manager->AddObject(
        std::make_unique< DerivedObject >()
        );
    object.SetSetting( setting );

    DoSomethingThatMayThrow();
}

int main(int argc, char* argv[])
{
  sm_manager = std::make_unique< ObjectManager >();

  AddDerivedManualManagment();
  AddDerivedManualManagmentUnsafe();
  AddDerivedManualManagmentWithUniquePtrUnsafe();
  AddDerivedSimple();
  AddDerivedWithSettingBefore(Setting::All);
  AddDerivedWithSettingBeforeNoMove(Setting::All);
  AddDerivedWithSettingAfter(Setting::All);
  return 0;
}
