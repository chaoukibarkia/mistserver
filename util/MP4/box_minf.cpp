#include "box.cpp"
#include <vector>
#include <string>

class Box_minf {
  public:
    Box_minf();
    ~Box_minf();
    Box * GetBox();
    void AddContent( Box * newcontent, uint32_t offset = 0 );
    void WriteContent( );
  private:
    Box * Container;
    
    std::vector<Box *> Content;
};//Box_ftyp Class

Box_minf::Box_minf( ) {
  Container = new Box( 0x6D696E66 );
}

Box_minf::~Box_minf() {
  delete Container;
}

Box * Box_minf::GetBox() {
  return Container;
}

void Box_minf::AddContent( Box * newcontent, uint32_t offset ) {
  if( offset >= Content.size() ) {
    Content.resize(offset+1);
  }
  if( Content[offset] ) {
    delete Content[offset];
  }
  Content[offset] = newcontent;
}

void Box_minf::WriteContent( ) {
  Container->ResetPayload( );
  Box * current;
  std::string serializedbox = "";
  for( uint32_t i = 0; i < Content.size(); i++ ) {
    current=Content[i];
    if( current ) {
      serializedbox.append((char*)current->GetBoxedData(),current->GetBoxedDataSize());
    }
  }
  Container->SetPayload((uint32_t)serializedbox.size(),(uint8_t*)serializedbox.c_str());
}
