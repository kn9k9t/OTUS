#pragma once
//-----------------------------------------------
#include "Primitives.h"
#include "FileHandler.h"
//-----------------------------------------------
/*
 * Interface to work with EditorController
 * */
class IEditorController
{
public:
  virtual ~IEditorController(){};
  virtual void onPrimitiveDeleted(const Primitive & primitive) = 0;
  virtual void onPrimitiveCreated(const Primitive & primitive) = 0;
  virtual void onPrimitiveChanged(const Primitive & primitive) = 0;
  virtual void onCloseUnsavedFile() = 0;
};
//-----------------------------------------------
class EditorController
{
public:
  EditorController(const IEditorController & user):
    _user(user),
    _fileHandler(),
    _isFileSaved(true){}

  VecPrimitives openFile(const std::string & path);
  void newFile(const std::string & path = "");
  void saveFile(const std::string & path);

  /*
   * @param primitive is primitive variant structure
   * */
  void createPrimitive(const Primitive & primitive);
  /*
   * @param primitive is primitive variant structure
   * */
  void deletePrimitive(const Primitive & primitive);
  /*
   * @param primitive is primitive variant structure
   * */
  void editPrimitive(const Primitive & primitive);
private:
  const IEditorController &        _user;
  const FileHandler<VecPrimitives> _fileHandler;
  VecPrimitives                    _primitives;
  bool                             _isFileSaved;
};
//-----------------------------------------------
