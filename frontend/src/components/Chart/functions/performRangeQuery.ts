import { Dispatch, SetStateAction } from 'react';
import { BASE_URL, ENDPOINTS } from '../../../apiConfig';
// import { Point } from '../../../types/Point';

export const performRangeQuery = async (
  selectionRect: {
    startX: number;
    startY: number;
    endX: number;
    endY: number;
  },
  dataStructure: string,
  setQueriedPoints: Dispatch<SetStateAction<never[]>>,
  setQueryTime: Dispatch<SetStateAction<number>>,
) => {
  const { startX, startY, endX, endY } = selectionRect;
  try {
    const response = await fetch(`${BASE_URL}${ENDPOINTS.RANGE_QUERY}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        startx: startX,
        starty: startY,
        endx: endX,
        endy: endY,
        structure_type: dataStructure,
      }),
    });

    if (!response.ok) {
      throw new Error('Failed to perform range query');
    }

    const data = await response.json();
    setQueriedPoints(data.points);
    setQueryTime(data.time_taken);
    console.log(data.points);
  } catch (error) {
    console.error('Error performing range query:', error);
  }
};
