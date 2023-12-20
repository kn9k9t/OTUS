#pragma once
//-----------------------------------------------
#include "EditorController.h"
//-----------------------------------------------
/*
 * Main class of editor with which user is interate
 * */
class UserInterface : public IEditorController
{
public:
  UserInterface(): _editor(*this){}

  void createPrimitive() {};
  void deletePrimitive() {};
  void editPrimitive() {};

  void openFile(const std::string & path);
  void newFile(const std::string & path = "");
  void saveFile(const std::string & path);

  virtual void onPrimitiveDeleted(const Primitive &) override {};
  virtual void onPrimitiveCreated(const Primitive &) override {};
  virtual void onPrimitiveChanged(const Primitive &) override {};
  virtual void onCloseUnsavedFile() override {};
private:
  EditorController _editor;
};
//-----------------------------------------------
