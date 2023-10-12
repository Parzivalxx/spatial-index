import React, { useState } from 'react';

interface GeneratePointsProps {
  onGeneratePoints: (numPoints: number) => void;
}

const GeneratePoints: React.FC<GeneratePointsProps> = ({ onGeneratePoints }) => {
  const [numPoints, setNumPoints] = useState<number>(1000);

  const handleGeneratePoints = () => {
    onGeneratePoints(numPoints);
  };

  return (
    <div className="container py-3">
      <label htmlFor="numPoints">Number of Points:</label>
      <div className="input-group">
        <input
          type="number"
          className="form-control me-4"
          id="numPoints"
          value={numPoints}
          onChange={(e) => setNumPoints(parseInt(e.target.value))}
        />
        <div className="input-group-append">
          <button className="btn btn-primary" type="button" onClick={handleGeneratePoints}>
            Generate
          </button>
        </div>
      </div>
    </div>
  );
};

export default GeneratePoints;
