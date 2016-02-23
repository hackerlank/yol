-------------------------------------------------------
-- �ļ�������diagrams.lua
-- �ļ���������������
-- �����ߡ���zhangzhixiong
-- ����ʱ�䣺2014-4-10
-------------------------------------------------------

local tb	= Task:GetTarget("FosterPet");
tb.szTargetName	= "FosterPet";
tb.REFRESH_FRAME	= 18;	-- һ����һ��

function tb:Init(szStaticDesc, szDynamicDesc, nPetType, nNature, nTargetRank, nTargetLevel)
	self.szStaticDesc	= szStaticDesc;
	self.szDynamicDesc	= szDynamicDesc;
	self.nPetType = nPetType;
	self.nNature = nNature;
	self.nTargetRank = nTargetRank
	self.nTargetLevel = nTargetLevel
end

function tb:Start()
	self.bDone = 1;
	local pPet = KPet.GetPetByTypeAndNature(self.nPetType, self.nNature)
	if pPet ~= null then
	    if pPet.GetRankLevel() < self.nTargetRank or self.nTargetLevel < nTargetLevel then
	        self.bDone = 0;
	    end
	else
	    self.bDone = 0;
	end

	if (self:IsDone()) then	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
		self.tbTask:OnFinishOneTag();
		return;
	end
	self:Register();
end

function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.bDone, 1);

	return 1;
end

function tb:Load(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.bDone		= self.me.pTask.GetTask(nGroupId, nStartTaskId);

	if (self.bDone ~= 1) then
		self:Register();
	end

	return 1;
end

function tb:IsDone()
	return self.bDone == 1;
end

function tb:GetDesc()
	return self.szDynamicDesc;
end

function tb:GetStaticDesc()
	return self.szStaticDesc;
end

function tb:Close(szReason)
	self:UnRegister();
end

function tb:Register()
	if (MODULE_GAMESERVER and not self.nRegisterId) then
		self.nRegisterId	= Timer:Register(self.REFRESH_FRAME, self.OnTimer, self);
	end
end

function tb:UnRegister()
	if (MODULE_GAMESERVER and self.nRegisterId) then
		Timer:Close(self.nRegisterId);
		self.nRegisterId	= nil;
	end
end

function tb:OnTimer()
	self.bDone = 1;
	local pPet = KPet.GetPetByTypeAndNature(self.nPetType, self.nNature)
	if pPet ~= null then
	    if pPet.GetRankLevel() < self.nTargetRank or self.nTargetLevel < nTargetLevel then
	        self.bDone = 0;
	    end
	else
	    self.bDone = 0;
	end

	if (self:IsDone()) then
		local tbSaveTask	= self.tbSaveTask;
		if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
			self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
			KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
		end

		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��

		self.tbTask:OnFinishOneTag();
	end
end