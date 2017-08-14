#include "Lift.h"

void main()
{
	LiftSystem::Instance()->init(10);

	Cmd* cmd = new Cmd;
	cmd->Type = CT_OPEN;
	LiftSystem::Instance()->addCmd(cmd);

	cmd = new Cmd;
	cmd->Type = CT_GO;
	cmd->Param1 = 8;
	LiftSystem::Instance()->addCmd(cmd);

	cmd = new Cmd;
	cmd->Type = CT_UP;
	cmd->Param1 = 5;
	LiftSystem::Instance()->addCmd(cmd);

	cmd = new Cmd;
	cmd->Type = CT_DOWN;
	cmd->Param1 = 4;
	LiftSystem::Instance()->addCmd(cmd);

	cmd = new Cmd;
	cmd->Type = CT_UP;
	cmd->Param1 = 4;
	LiftSystem::Instance()->addCmd(cmd);

	LiftSystem::Instance()->reorderCmd(CT_UP);

	char c;
	std::cin >> c;
}