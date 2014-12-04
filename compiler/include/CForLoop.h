/*
 * Copyright 2004-2014 Cray Inc.
 * Other additional copyright holders may be indicated within.
 *
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _CFOR_LOOP_H_
#define _CFOR_LOOP_H_

#include "stmt.h"

class ForLoop;

class CForLoop : public BlockStmt
{
  //
  // Class interface
  //
public:
  static BlockStmt*      buildCForLoop(CallExpr*  cforInfo,
                                       BlockStmt* body);

  static CForLoop*       buildWithBodyFrom(ForLoop* forLoop);

  static CForLoop*       loopForClause(BlockStmt* clause);

  //
  // Instance Interface
  //
public:
  virtual               ~CForLoop();

  virtual CForLoop*      copy(SymbolMap* map = NULL, bool internal = false);

  virtual GenRet         codegen();
  virtual void           verify();
  virtual void           accept(AstVisitor* visitor);

  virtual Expr*          getFirstExpr();
  virtual Expr*          getNextExpr(Expr* expr);

  virtual bool           isLoop()                                     const;
  virtual bool           isCForLoop()                                 const;

  virtual bool           deadBlockCleanup();

  void                   loopHeaderSet(BlockStmt* initBlock,
                                       BlockStmt* testBlock,
                                       BlockStmt* incrBlock);

  // NOAKES 2014/11/26 Transitional
  CallExpr*              cforInfoGet()                                const;

  virtual CallExpr*      blockInfoGet()                               const;
  virtual CallExpr*      blockInfoSet(CallExpr* expr);

private:
                         CForLoop();

                         CForLoop(BlockStmt* body);

  std::string            codegenCForLoopHeader   (BlockStmt* block);
  GenRet                 codegenCForLoopCondition(BlockStmt* block);
};

#endif
